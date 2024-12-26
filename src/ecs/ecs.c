#include "ecs.h"


ecs_t* ecs_create(const SceneID scene_id) {
	ecs_t* ecs = (ecs_t*)malloc(sizeof(ecs_t));
	assert(ecs != NULL);
	entity_manager_init(&ecs->entity);
	system_manager_init(&ecs->system);
	component_manager_init(&ecs->component);
	camera_init(&ecs->camera);
	vector_init(&ecs->entities_to_destroy, sizeof(entity_t), MAX_ENTITIES);
	ecs->should_destroy_all_entities = 0;
	ecs->scene_id = scene_id;
	return ecs;
}

void ecs_destroy(ecs_t* ecs) {
	if (ecs == NULL) {
		return;
	}
	entity_manager_close(&ecs->entity);
	component_manager_close(&ecs->component);
	system_manager_close(&ecs->system);
	camera_close(&ecs->camera);
	vector_close(&ecs->entities_to_destroy);
	free(ecs);
}

entity_t ecs_create_entity(
	ecs_t* ecs, 
	const zindex_t zindex, 
	const int should_add_to_camera
) {
	const entity_t e = entity_manager_create_entity(&ecs->entity);
	transform_t* t = ecs_get_transform(ecs, e);
	transform_init(t, zindex);
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

float ecs_entity_centery(ecs_t* ecs, const entity_t e) {
	const transform_t* t = ecs_get_transform(ecs, e);
	return t->pos.y + t->size.y / 2.0f;
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
	system_manager_update(&ecs->system, dt);

	if (ecs->should_destroy_all_entities) {
		ecs->should_destroy_all_entities = 0;
		entity_manager_clear(&ecs->entity);	
		system_manager_clear(&ecs->system);
		camera_clear(&ecs->camera);
		vector_clear(&ecs->entities_to_destroy);
	}

	while (!vector_is_empty(&ecs->entities_to_destroy)) {
		const entity_t* e = (entity_t*) vector_back(&ecs->entities_to_destroy);		
		camera_erase(&ecs->camera, *e, ecs_get_transform(ecs, *e)->zindex);
		entity_manager_destroy_entity(&ecs->entity, *e);
		system_manager_destroy_entity(&ecs->system, *e);
		vector_erase_back(&ecs->entities_to_destroy);
	}
}

void ecs_draw(ecs_t* ecs) {
	// Draw entities using zindex order
	for (int i = CAMERA_ZINDEX_MIN; i <= CAMERA_ZINDEX_MAX; i++) {
		vector_t* vec = ecs->camera.entities + i;
		iterator_t iter = vector_iter(vec);
		// Update entity centery position
		for (entity_pair_t* p = iter.begin; p < iter.end; p++) {
			const transform_t* t = ecs_get_transform(ecs, p->e);
			p->centery = t->pos.y + t->size.y / 2.0f;
		}
		// Sort entities by centery position
		qsort(
			vec->data,
			vec->size,
			vec->v_size,
			entity_pair_compare
		);
		// Draw entities
		for (entity_pair_t* p = iter.begin; p < iter.end; p++) {			
			hash_set_t* components = ecs->system.entities_to_drawable_components + p->e; // Drawable components of entity
			for (vector_t* bucket = components->buckets; bucket < components->buckets + components->n_buckets; bucket++) {
				iterator_t hash_iter = vector_iter(bucket);
				for (component_t* id = hash_iter.begin; id < hash_iter.end; id++) {
					ecs->system.system[*id].draw(p->e);					
				}
			}			
		}
	}
}

entity_t ecs_create_sprite(
	ecs_t* ecs,
	const char* filepath,
	const float pos_x,
	const float pos_y,
	const zindex_t zindex
) {
	const entity_t e = ecs_create_entity(ecs, zindex, 1);
	sprite_t* sprite = (sprite_t*)ecs_add_component(ecs, e, SPRITE_ID);
	sprite_init(sprite, filepath);
	transform_t* transform = ecs_get_transform(ecs, e);
	transform->pos = (Vector2){ pos_x, pos_y };
	transform->size = (Vector2){ (float) sprite->texture->width, (float) sprite->texture->height };
	return e;
}

transform_t* ecs_get_transform(ecs_t* ecs, const entity_t e) {
	return (transform_t*)component_manager_get_component(&ecs->component, e, TRANSFORM_ID);
}

size_t ecs_num_entities_on_camera(ecs_t* ecs) {
	return camera_num_entities(&ecs->camera);
}

size_t ecs_num_alive_entities(ecs_t* ecs) {
	return entity_manager_num_alive_entities(&ecs->entity);
}