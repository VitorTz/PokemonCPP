#include "ecs.h"


void ecs_init(ECS* ecs) {
	ecs->entity = entity_manager_create();
	ecs->component = component_manager_create();
	ecs->system = system_manager_create();
	ecs->camera = camera_create();
	vector_init(&ecs->entities_to_destroy, sizeof(entity_t), MAX_ENTITIES);
	ecs->should_destroy_all_entities = 0;

	// Components
	component_manager_register_component(ecs->component, TRANSFORM_ID, sizeof(EntityTransform));
	component_manager_register_component(ecs->component, SPRITE_ID, sizeof(Sprite));
	component_manager_register_component(ecs->component, SPRITE_ANIMATION_ID, sizeof(SpriteAnimation));

	// Systems
	system_manager_register_system(ecs->system, TRANSFORM_ID, NULL, NULL);
	system_manager_register_system(ecs->system, SPRITE_ID, NULL, sprite_draw);
	system_manager_register_system(ecs->system, SPRITE_ANIMATION_ID, sprite_animation_update, sprite_animation_draw);
}

void ecs_close(ECS* ecs) {
	entity_manager_destroy(ecs->entity);
	component_manager_destroy(ecs->component);
	system_manager_destroy(ecs->system);
	camera_destroy(ecs->camera);
	vector_close(&ecs->entities_to_destroy);	
}

void ecs_create_entity(ECS* ecs, const zindex_t zindex, const int should_add_to_camera) {
	const entity_t e = entity_manager_create_entity(&ecs->entity);
	entity_tranform_init(ecs_get_transform(ecs, e), zindex);
	if (should_add_to_camera) {
		camera_insert(ecs->camera, e, zindex);
	}
	return e;
}

void ecs_destroy_entity(ECS* ecs, const entity_t e) {
	vector_push_back(ecs->entity, &e);
}

void ecs_destroy_all_entities(ECS* ecs) {
	ecs->should_destroy_all_entities = 1;
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

void ecs_update(ECS* ecs, const float dt) {
	system_manager_update(&ecs->system, dt);

	if (ecs->should_destroy_all_entities) {
		ecs->should_destroy_all_entities = 0;
		entity_manager_clear(&ecs->entity);
		system_manager_clear(&ecs->system);
		camera_clear(ecs->camera);
		vector_clear(&ecs->entities_to_destroy);
	}

	entity_t* begin = (entity_t*)vector_begin(&ecs->entities_to_destroy);
	entity_t* end = (entity_t*)vector_end(&ecs->entities_to_destroy);
	for (entity_t* p = begin; p < end; p++) {
		camera_erase(ecs->camera, *p, ecs_get_transform(ecs, *p)->zindex);
		entity_manager_destroy_entity(ecs->entity, *p);
		system_manager_destroy_entity(ecs->system, *p);
	}
	vector_clear(&ecs->entities_to_destroy);
}

static int cmp_entity_pair(const void* l, const void* r) {
	const EntityPair* a = l;
	const EntityPair* b = r;	
	if (a->centery == b->centery) return 0;
	return a->centery < b->centery ? -1 : 1;	
}

void ecs_draw(ECS* ecs) {
	for (zindex_t z = CAMERA_ZINDEX_MIN; z <= CAMERA_ZINDEX_MAX; z++) {
		Vector* vec = ecs->camera->zindex + z;
		EntityPair* begin = (EntityPair*)vector_begin(vec);
		EntityPair* end = (EntityPair*)vector_end(vec);
		for (EntityPair* p = begin; p < end; p++) {
			const EntityTransform* transform = component_manager_at(ecs->component, p->entity, TRANSFORM_ID);
			p->centery = transform->pos.y + transform->size.y / 2.0f;
		}
		qsort(begin, vec->size, sizeof(EntityPair), cmp_entity_pair);
		system_manager_draw(ecs->system, begin, end);
	}
}

EntityTransform* ecs_get_transform(ECS* ecs, const entity_t e) {
	return component_manager_at(&ecs->component, e, TRANSFORM_ID);
}
