#include "ecs.h"
#include "ecs_manager.h"


ECS* ecs_create(const SceneID scene_id) {
	ECS* ecs = (ECS*)malloc(sizeof(ECS));
	assert(ecs != NULL);
	
	// ECS
	ecs->entity = entity_manager_create();
	ecs->component = component_manager_create();
	ecs->system = system_manager_create();
	ecs->camera = camera_create();
	ecs->entities_to_destroy = vector_create(sizeof(entity_t), MAX_ENTITIES);
	ecs->static_collisions = vector_create(sizeof(Rectangle), 1024);
	ecs->should_destroy_all_entities = 0;
	ecs->mouse_zoom_is_enable = 1;
	ecs->scene_id = scene_id;

	// Component
	component_manager_register_component(ecs->component, TRANSFORM_ID, sizeof(EntityTransform));
	component_manager_register_component(ecs->component, SPRITE_ID, sizeof(Sprite));
	component_manager_register_component(ecs->component, SPRITE_ANIMATION_ID, sizeof(SpriteAnimation));
	component_manager_register_component(ecs->component, SHADOW_ID, sizeof(Shadow));

	// System
	system_manager_register_system(ecs->system, TRANSFORM_ID, NULL, NULL);
	system_manager_register_system(ecs->system, SPRITE_ID, NULL, sprite_draw);
	system_manager_register_system(ecs->system, SPRITE_ANIMATION_ID, sprite_animation_update, sprite_animation_draw);
	system_manager_register_system(ecs->system, SHADOW_ID, NULL, shadow_draw);

	return ecs;
}

void ecs_destroy(ECS* ecs) {
	entity_manager_destroy(ecs->entity);
	component_manager_destroy(ecs->component);
	system_manager_destroy(ecs->system);
	camera_destroy(ecs->camera);
	vector_destroy(ecs->entities_to_destroy);
	vector_destroy(ecs->static_collisions);
	free(ecs);
}

entity_t ecs_create_entity(ECS* ecs, const zindex_t zindex, const int should_add_to_camera) {
	assert(zindex >= CAMERA_ZINDEX_MIN && zindex <= CAMERA_ZINDEX_MAX);
	const entity_t e = entity_manager_create_entity(ecs->entity);
	EntityTransform* transform = (EntityTransform*)ecs_add_component(ecs, e, TRANSFORM_ID);
	entity_tranform_init(transform, zindex);
	if (should_add_to_camera) {
		camera_insert(ecs->camera, e, zindex);
	}
	return e;
}

entity_t ecs_create_sprite(ECS* ecs, const zindex_t zindex, const char* filepath) {	
	const entity_t e = ecs_create_entity(ecs, zindex, 1);
	EntityTransform* trasnform = ecs_get_transform(ecs, e);
	Sprite* sprite = (Sprite*) ecs_add_component(ecs, e, SPRITE_ID);
	sprite_init(sprite, filepath);
	trasnform->size = sprite->size;	
	return e;
}

entity_t ecs_create_ground_sprite(ECS* ecs, const char* filepath) {
	const entity_t e = ecs_create_sprite(ecs, CAMERA_ZINDEX_GROUND, filepath);
	EntityTransform* transform = ecs_get_transform(ecs, e);
	camera_set_horizontal_limit(ecs->camera, SCREEN_W, transform->size.x);
	camera_set_vertical_limit(ecs->camera, SCREEN_H, transform->size.y);
	return e;
}

void ecs_add_shadow(ECS* ecs, const entity_t e, const float x_offset, const float y_offset) {
	Shadow* shadow = (Shadow*) ecs_add_component(ecs, e, SHADOW_ID);
	shadow_init(shadow, (Vector2) { x_offset, y_offset }, GRAPHICS_PATH "other/shadow.png");
}

void ecs_destroy_entity(ECS* ecs, const entity_t e) {
	vector_push_back(ecs->entities_to_destroy, &e);
}

void ecs_destroy_all_entities(ECS* ecs) {
	ecs->should_destroy_all_entities = 1;
}

void ecs_add_static_collision(ECS* ecs, const Rectangle rect) {
	vector_push_back(ecs->static_collisions, &rect);
}

void* ecs_add_component(ECS* ecs, const entity_t e, const component_t component_id) {
	system_manager_insert(ecs->system, e, component_id);
	return component_manager_at(ecs->component, e, component_id);
}

void* ecs_get_component(ECS* ecs, const entity_t e, const component_t component_id) {
	return component_manager_at(ecs->component, e, component_id);
}

void ecs_rmv_component(ECS* ecs, const entity_t e, const component_t component_id) {
	system_manager_erase(ecs->system, e, component_id);
}

int ecs_check_static_collision(ECS* ecs, const Rectangle rect) {
	Rectangle* begin = (Rectangle*)vector_begin(ecs->static_collisions);
	Rectangle* end = (Rectangle*)vector_end(ecs->static_collisions);
	for (Rectangle* p = begin; p < end; p++) {
		if (CheckCollisionRecs(rect, *p)) {
			return 1;
		}
	}
	return 0;
}

void ecs_update(ECS* ecs, const float dt) {
	if (ecs->mouse_zoom_is_enable) {
		camera_handle_zoom(ecs->camera, dt);
	}

	ecs_manager_set_ecs_instance(ecs->scene_id);

	system_manager_update(ecs->system, dt);

	if (ecs->should_destroy_all_entities) {
		entity_manager_clear(ecs->entity);
		system_manager_clear(ecs->system);
		camera_clear(ecs->camera);
		vector_clear(ecs->entities_to_destroy);
		ecs->should_destroy_all_entities = 0;
	}

	if (ecs->entities_to_destroy->size > 0) {
		entity_t* begin = (entity_t*) vector_begin(ecs->entities_to_destroy);
		entity_t* end = (entity_t*) vector_end(ecs->entities_to_destroy);
		for (entity_t* p = begin; p < end; p++) {
			camera_erase(ecs->camera, *p, ecs_get_transform(ecs, *p)->zindex);
			entity_manager_destroy_entity(ecs->entity, *p);
			system_manager_destroy_entity(ecs->system, *p);
		}
		ecs->entities_to_destroy->size = 0;
	}
}

static int cmp_entity_pair(const void* l, const void* r) {
	const EntityPair* a = l;
	const EntityPair* b = r;	
	if (a->centery == b->centery) return 0;
	return a->centery < b->centery ? -1 : 1;	
}

void ecs_draw(ECS* ecs) {	
	ecs_manager_set_ecs_instance(ecs->scene_id);
	camera_begin_drawing(ecs->camera);
		for (zindex_t z = CAMERA_ZINDEX_MIN; z <= CAMERA_ZINDEX_MAX; z++) {
			Vector* vec = ecs->camera->zindex + z;
			EntityPair* begin = (EntityPair*) vector_begin(vec);
			EntityPair* end = (EntityPair*) vector_end(vec);
			for (EntityPair* p = begin; p < end; p++) {
				const EntityTransform* transform = component_manager_at(ecs->component, p->entity, TRANSFORM_ID);
				p->centery = transform->pos.y + transform->size.y / 2.0f;
			}
			qsort(begin, vec->size, sizeof(EntityPair), cmp_entity_pair);
			system_manager_draw(ecs->system, begin, end);
		}
	camera_end_drawing();
}

SetIterator* ecs_get_entities_by_component(ECS* ecs, component_t component_id) {
	return set_iter(ecs->system->entities + component_id);
}

EntityTransform* ecs_get_transform(ECS* ecs, const entity_t e) {
	return (EntityTransform*) component_manager_at(ecs->component, e, TRANSFORM_ID);
}
