#include "ecs.h"


void ecs_init(ecs_t* ecs) {
	entity_manager_init(&ecs->entity);
	component_manager_init(&ecs->component);
	sytem_manager_init(&ecs->system);
	vector_init(&ecs->entities_to_destroy, sizeof(entity_t), MAX_ENTITIES);
	camera_init(&ecs->camera);
	ecs->should_destroy_all_entities = 0;
}

void ecs_close(ecs_t* ecs) {
	entity_manager_close(&ecs->entity);
	component_manager_close(&ecs->component);
	sytem_manager_close(&ecs->system);
	vector_close(&ecs->entities_to_destroy);
	camera_close(&ecs->camera);	
}

entity_t ecs_create_entity(ecs_t* ecs, const zindex_t zindex, const int should_add_to_camera) {
	const entity_t e = entity_manager_create_entity(&ecs->entity);
	transform_init(ecs_get_transform(ecs, e), zindex);
	if (should_add_to_camera) {
		camera_insert(&ecs->camera, e, zindex);
	}
	return e;
}

entity_t ecs_create_sprite(
	ecs_t* ecs, 
	const zindex_t zindex, 
	const float pos_x, 
	const float pos_y, 
	const char* imagepath
) {
	const entity_t e = entity_manager_create_entity(&ecs->entity);
	transform_t* t = ecs_get_transform(ecs, e);
	transform_init(t, zindex);
	sprite_t* sprite = (sprite_t*) ecs_add_component(ecs, e, SPRITE_ID);	
	t->pos = (Vector2){ pos_x, pos_y };
	t->size = (Vector2){ (float)sprite->texture->width, (float)sprite->texture->height };
	return e;
}

void ecs_destroy_entity(ecs_t* ecs, const entity_t e) {
	vector_push_back(&ecs->entities_to_destroy, &e);
}

void ecs_destroy_all_entities(ecs_t* ecs) {
	ecs->should_destroy_all_entities = 1;
}

void* ecs_add_component(ecs_t* ecs, const entity_t e, const component_t component_id) {
	sytem_manager_insert(&ecs->system, e, component_id);
	return component_manager_get_component(&ecs->component, e, component_id);
}

void* ecs_get_component(ecs_t* ecs, const entity_t e, const component_t component_id) {
	return component_manager_get_component(&ecs->component, e, component_id);
}

void ecs_rmv_componetn(ecs_t* ecs, const entity_t e, const component_t component_id) {
	system_manager_erase(&ecs->system, e, component_id);
}

void ecs_update(ecs_t* ecs, const float dt) {
	system_manager_update(&ecs->system, SPRITE_ANIMATION_ID, dt);

	if (ecs->should_destroy_all_entities) {
		ecs->should_destroy_all_entities = 0;
		entity_manager_clear(&ecs->entity);
		system_manager_clear(&ecs->system);
		vector_clear(&ecs->entities_to_destroy);		
		camera_clear(&ecs->camera);
	}

	entity_t* begin = (entity_t*) vector_begin(&ecs->entities_to_destroy);
	entity_t* end = (entity_t*) vector_end(&ecs->entities_to_destroy);
	for (entity_t* e = begin; e < end; e++) {
		camera_erase(&ecs->camera, *e, ecs_get_transform(ecs, *e)->zindex);
		entity_manager_destroy_entity(&ecs->entity, *e);
		system_manager_clear(&ecs->system);
	}
	vector_clear(&ecs->entities_to_destroy);
}

void ecs_draw(ecs_t* ecs) {
	for (zindex_t zindex = CAMERA_ZINDEX_MIN; zindex <= CAMERA_ZINDEX_MAX; zindex++) {
		vector_t* vec = ecs->camera.entities + zindex;
		entity_pair_t* begin = (entity_pair_t*) vector_begin(vec);
		entity_pair_t* end = (entity_pair_t*)vector_end(vec);
		for (entity_pair_t* p = begin; p < end; p++) {
			const transform_t* transform = (transform_t*)component_manager_get_component(&ecs->component, p->entity, TRANSFORM_ID);
			p->centery = transform->pos.y + transform->size.y / 2.0f;
		}
		qsort(
			begin,
			vec->size,
			sizeof(entity_pair_t),
			entity_pair_compare
		);
		system_manager_draw(&ecs->system, begin, end);
	}
}

void ecs_reset(ecs_t* ecs) {
	entity_manager_clear(&ecs->entity);
	system_manager_clear(&ecs->system);
	vector_clear(&ecs->entities_to_destroy);
	camera_clear(&ecs->camera);
	ecs->should_destroy_all_entities = 0;
}

transform_t* ecs_get_transform(ecs_t* ecs, const entity_t e) {
	return (transform_t*)component_manager_get_component(&ecs->component, e, TRANSFORM_ID);
}
