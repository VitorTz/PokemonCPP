#include "ecs.h"


void ecs_init(ecs_t* ecs) {
	entity_manager_init(&ecs->entity);
	component_manager_init(&ecs->component);
	system_manager_init(&ecs->system);
	vector_init(&ecs->entities_to_destroy, sizeof(entity_t), MAX_ENTITIES);
	camera_init(&ecs->camera);
	ecs->should_destroy_all_entities = 0;
}

void ecs_close(ecs_t* ecs) {
	entity_manager_close(&ecs->entity);
	component_manager_close(&ecs->component);
	system_manager_close(&ecs->system);
	vector_close(&ecs->entities_to_destroy);
	camera_close(&ecs->camera);	
}

transform_t* ecs_get_transform(ecs_t* ecs, const entity_t e) {
	return (transform_t*)component_manager_get_component(&ecs->component, e, TRANSFORM_ID);
}

entity_t ecs_create_entity(ecs_t* ecs, const zindex_t zindex, const int should_add_to_camera) {
	const entity_t e = entity_manager_create_entity(&ecs->entity);
	transform_init(ecs_get_transform(ecs, e), zindex);
	if (should_add_to_camera) {
		camera_insert(&ecs->camera, e, zindex);
	}
	return e;
}

void* ecs_add_component(ecs_t* ecs, const entity_t e, const component_t component_id) {
	system_manager_insert(&ecs->system, e, component_id);
	return component_manager_get_component(&ecs->component, e, component_id);
}

entity_t ecs_create_sprite(
	ecs_t* ecs, 
	const zindex_t zindex, 
	const float pos_x, 
	const float pos_y, 
	const char* imagepath
) {
	const entity_t e = ecs_create_entity(ecs, zindex, 1);	 
	sprite_t* sprite = (sprite_t*) ecs_add_component(ecs, e, SPRITE_ID);
	sprite_init(sprite, imagepath);
	transform_t* t = ecs_get_transform(ecs, e);	
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

	if (ecs->entities_to_destroy.size) {
		entity_t* begin = (entity_t*) vector_begin(&ecs->entities_to_destroy);
		entity_t* end = (entity_t*) vector_end(&ecs->entities_to_destroy);
		for (entity_t* e = begin; e < end; e++) {
			camera_erase(&ecs->camera, *e, ecs_get_transform(ecs, *e)->zindex);
			entity_manager_destroy_entity(&ecs->entity, *e);
			system_manager_destroy_entity(&ecs->system, *e);			
		}
		vector_clear(&ecs->entities_to_destroy);
	}
}

void ecs_draw(ecs_t* ecs) {
	for (zindex_t zindex = CAMERA_ZINDEX_MIN; zindex <= CAMERA_ZINDEX_MAX; zindex++) {
		vector_t* vec = ecs->camera.entities + zindex;		
		for (entity_pair_t* p = vector_begin(vec); p < vector_end(vec); p++) {
			const transform_t* transform = ecs_get_transform(ecs, p->entity);
			p->centery = transform->pos.y + transform->size.y / 2.0f;
		}
		vector_sort(vec, entity_pair_compare);	
		system_manager_draw(&ecs->system, vector_begin(vec), vector_end(vec));
	}
}

void ecs_reset(ecs_t* ecs) {
	entity_manager_clear(&ecs->entity);
	system_manager_clear(&ecs->system);
	vector_clear(&ecs->entities_to_destroy);
	camera_clear(&ecs->camera);
	ecs->should_destroy_all_entities = 0;
}
