#include "ecs.h"


ecs_t* ecs_create() {
	ecs_t* ecs = (ecs_t*)malloc(sizeof(ecs_t));
	ecs->entity = entity_manager_create();
	ecs->component = component_manager_create();
	ecs->system = system_manager_create();
	ecs->camera = camera_create();
	ecs->entities_to_destroy = vector_create(sizeof(entity_t), MAX_ENTITIES / 4);
	ecs->should_destroy_all_entities = 0;
	ecs->collisions = vector_create(sizeof(Rectangle), 1024);
	ecs->transitions = vector_create(sizeof(transition_t), (size_t) NumScenes);
	return ecs;
}


void ecs_init(ecs_t* ecs) {
	ecs->entity = entity_manager_create();
	ecs->component = component_manager_create();
	ecs->system = system_manager_create();
	ecs->camera = camera_create();
	ecs->entities_to_destroy = vector_create(sizeof(entity_t), MAX_ENTITIES / 4);
	ecs->should_destroy_all_entities = 0;
	ecs->collisions = vector_create(sizeof(Rectangle), 1024);
	ecs->transitions = vector_create(sizeof(transition_t), (size_t)NumScenes);
}


void ecs_destroy(ecs_t* ecs) {
	entity_manager_destroy(ecs->entity);
	component_manager_destroy(ecs->component);
	system_manager_destroy(ecs->system);
	vector_destroy(ecs->entities_to_destroy);
	vector_destroy(ecs->collisions);
	vector_destroy(ecs->transitions);
	free(ecs);
}


void ecs_close(ecs_t* ecs) {
	entity_manager_destroy(ecs->entity);
	component_manager_destroy(ecs->component);
	system_manager_destroy(ecs->system);
	vector_destroy(ecs->entities_to_destroy);
	vector_destroy(ecs->collisions);
	vector_destroy(ecs->transitions);
}


entity_t ecs_create_entity(ecs_t* ecs, const zindex_t z, const int add_to_camera) {
	const entity_t e = entity_manager_create_entity(ecs->entity);
	transform_t* t = (transform_t*) component_manager_at(ecs->component, e, TRANSFORM_ID);
	transform_init(t, z);	
	if (add_to_camera) {
		camera_insert(ecs->camera, e, z);
	}
	return e;
}


void ecs_destroy_entity(ecs_t* ecs, const entity_t e) {
	vector_push_back(ecs->entities_to_destroy, &e);
}


void ecs_add_collisions(
	ecs_t* ecs, 
	const float x, 
	const float y,
	const float width, 
	const float height
) {
	Rectangle rect = (Rectangle){ x, y, width, height };
	vector_push_back(ecs->collisions, &rect);
}


void ecs_add_transition(
	ecs_t* ecs, 
	const enum SceneID scene_id, 
	const float x, 
	const float y, 
	const float width, 
	const float height
) {
	transition_t t = (transition_t){ scene_id, (Rectangle) { x, y, width, height } };
	vector_push_back(ecs->transitions, &t);
}


void* ecs_component_at(ecs_t* ecs, const entity_t e, const component_t id) {
	return component_manager_at(ecs->component, e, id);
}


transform_t* ecs_get_transform(ecs_t* ecs, const entity_t e) {
	return (transform_t*) component_manager_at(ecs->component, e, TRANSFORM_ID);
}


void* ecs_component_insert(ecs_t* ecs, const entity_t e, const component_t id) {
	system_manager_insert(ecs->system, e, id);
	return component_manager_at(ecs->component, e, id);
}


void ecs_update(ecs_t* ecs, const float dt) {
	system_manager_update(ecs->system, dt);

	if (ecs->should_destroy_all_entities) {
		ecs->should_destroy_all_entities = 0;
		vector_clear(ecs->entities_to_destroy);
		camera_clear(ecs->camera);
		entity_manager_clear(ecs->entity);
		system_manager_clear(ecs->system);
	}

	while (!vector_is_empty(ecs->entities_to_destroy)) {
		entity_t e;
		vector_pop_back(ecs->entities_to_destroy, &e);
		camera_erase(ecs->camera, e, ecs_get_transform(ecs, e)->zindex);
		entity_manager_destroy_entity(ecs->entity, e);
		system_manager_destroy_entity(ecs->system, e);
	}
}


static void comp_entity_pair(const void* l, const void* r) {
	return ((entity_pair_t*)l)->y < ((entity_pair_t*)r)->y;
}


void ecs_draw(ecs_t* ecs) {
	for (int i = 0; i < CAMERA_ZINDEX_MAX; i++) {
		vector_t* vec = ecs->camera->entities + i;
		const iterator_t iter = vector_iter(vec);
		for (entity_pair_t* pair = iter.begin; pair < iter.end; pair++) {
			const transform_t* t = component_manager_at(ecs->component, pair->e, TRANSFORM_ID);
			pair->y = t->pos.y + t->size.y / 2.0f;
		}
		qsort(vec->data, vec->size, sizeof(entity_pair_t), comp_entity_pair);
		system_manager_draw(ecs->system, vector_iter(vec));
	}
}


void ecs_destroy_all_entities(ecs_t* ecs) {
	ecs->should_destroy_all_entities = 1;
}