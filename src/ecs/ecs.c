#include "ecs.h"


void ecs_init(ecs_t* ecs, const SceneID scene_id) {
	entity_manager_init(&ecs->entity);
	component_manager_init(&ecs->component);
	system_manager_init(&ecs->system);
	vector_init(&ecs->entities_to_destroy, sizeof(entity_t), MAX_ENTITIES);
	camera_init(&ecs->camera);
	ecs->should_destroy_all_entities = 0;
	ecs->scene_id = scene_id;
}

void ecs_close(ecs_t* ecs) {
	entity_manager_close(&ecs->entity);
	component_manager_close(&ecs->component);
	system_manager_close(&ecs->system);
	vector_close(&ecs->entities_to_destroy);
	camera_close(&ecs->camera);
}

entity_t ecs_create_entity(ecs_t* ecs, const zindex_t zindex, const int should_add_to_camera) {
	const entity_t e = entity_manager_create_entity(&ecs->entity);
	transform_t* transform = ecs_get_transform(ecs, e);
	transform_init(transform, zindex);
	if (should_add_to_camera) {
		camera_insert(&ecs->camera, e, zindex);
	}
	return e;
}

void ecs_destroy_entity(ecs_t* ecs, const entity_t e) {
	vector_push_back(&ecs->entities_to_destroy, &e);
}

void ecs_destroy_all_entities(ecs_t* ecs) {
	ecs->should_destroy_all_entities = 1;
}

void* ecs_add_component(ecs_t* ecs, const entity_t e, const component_t component_id) {
	system_manager_insert(&ecs->system, e, component_id);
	return component_manager_get_component(&ecs->component, e, component_id);
}

void* ecs_get_component(ecs_t* ecs, const entity_t e, const component_t component_id) {
	return component_manager_get_component(&ecs->component, e, component_id);
}

void ecs_rmv_component(ecs_t* ecs, const entity_t e, const component_t component_id) {
	system_manager_erase(&ecs->system, e, component_id);
}


void ecs_update(ecs_t* ecs, const float dt) {
	ecs->system.system_arr[SPRITE_ANIMATION_ID].update(
		set_iter(ecs->system.component_to_entities + SPRITE_ANIMATION_ID),
		dt
	);

	if (ecs->should_destroy_all_entities) {
		ecs->should_destroy_all_entities = 0;
		entity_manager_clear(&ecs->entity);
		system_manager_clear(&ecs->system);
		camera_clear(&ecs->camera);
		vector_clear(&ecs->entities_to_destroy);
	}

	while (ecs->entities_to_destroy.size > 0) {
		entity_t e;
		vector_pop_back(&ecs->entities_to_destroy, &e);
		camera_erase(&ecs->camera, e, ecs_get_transform(ecs, e)->zindex);
		entity_manager_destroy_entity(&ecs->entity, e);
		system_manager_destroy_entity(&ecs->component, e);
	}
}

void ecs_draw(ecs_t* ecs) {
	for (int i = CAMERA_ZINDEX_MIN; i <= CAMERA_ZINDEX_MAX; i++) {
		vector_t* vec = ecs->camera.entities + i;
		vector_iterator_t iter = vector_iter(vec);
		for (entity_pair_t* pair = iter.begin; pair < iter.end; pair++) {
			const transform_t* transform = component_manager_get_component(&ecs->component, pair->e, TRANSFORM_ID);
			pair->centery = transform->pos.y + transform->size.y / 2.0f;
		}
		qsort(
			vec->data,
			vec->size,
			vec->type_size,
			entity_pair_compare
		);
		for (entity_pair_t* pair = iter.begin; pair < iter.end; pair++) {			
			vector_t* v = ecs->system.entities_to_drawable_components + pair->e;
			vector_iterator_t v_iter = vector_iter(v);
			for (component_t* id = v_iter.begin; id < v_iter.end; id++) {
				ecs->system.system_arr[*id].draw(pair->e);
			}
		}
	}
}

entity_t ecs_create_sprite(
	ecs_t* ecs,
	const char* filepath,
	float pos_x,
	float pos_y,
	zindex_t zindex
) {
	const entity_t e = ecs_create_entity(ecs, zindex, 1);
	sprite_t* sprite = (sprite_t*) ecs_add_component(ecs, e, SPRITE_ID);
	sprite_init(sprite, filepath);
	transform_t* transform = ecs_get_transform(ecs, e);
	transform->pos = (Vector2){ pos_x, pos_y };
	transform->size = (Vector2){ (float) sprite->texture->width, (float)sprite->texture->height };
	return e;
}

transform_t* ecs_get_transform(ecs_t* ecs, const entity_t e) {
	return component_manager_get_component(&ecs->component, e, TRANSFORM_ID);
}

size_t ecs_num_alive_entities(const ecs_t* ecs) {
	return entity_manager_num_alive_entities(&ecs->entity);
}