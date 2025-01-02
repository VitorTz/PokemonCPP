#include "system_manager.h"
#include "../util/hash.h"



SystemManager* system_manager_create() {
	SystemManager* system_manager = (SystemManager*)malloc(sizeof(SystemManager));
	assert(system_manager != NULL);
	
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		set_init(system_manager->entities + i, sizeof(entity_t), hash_component_id);
		system_manager->is_drawable_component[i] = 0;
	}

	for (int i = 0; i < MAX_ENTITIES; i++) {
		set_init(system_manager->drawable_components + i, sizeof(component_t), hash_entity_id);
	}
	return system_manager;
}

void system_manager_register_system(
	SystemManager* system_manager,
	component_t id,
	void (*update)(SetIterator*, float),
	void (*draw)(entity_t)
) {
	system_manager->system[id] = (System){ update, draw };
	if (draw != NULL) {
		system_manager->is_drawable_component[id] = 1;
	}
}

void system_manager_destroy(SystemManager* system_manager) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		set_close(system_manager->entities + i);
	}

	for (int i = 0; i < MAX_ENTITIES; i++) {
		set_close(system_manager->drawable_components + i);
	}
	free(system_manager);
}

void system_manager_insert(SystemManager* system_manager, const entity_t entity, const component_t component_id) {
	set_insert(system_manager->entities + component_id, &entity);
	if (system_manager->is_drawable_component[component_id]) {
		set_insert(system_manager->drawable_components + entity, &component_id);
	}
}

void system_manager_erase(SystemManager* system_manager, const entity_t entity, const component_t component_id) {
	set_erase(system_manager->entities + component_id, &entity);
	set_erase(system_manager->drawable_components + entity, &component_id);
}

void system_manager_destroy_entity(SystemManager* system_manager, const entity_t entity) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		set_erase(system_manager->entities + i, &entity);
	}
	set_clear(system_manager->drawable_components + entity);
}

void system_manager_update(SystemManager* system_manager, const float dt) {
	system_manager->system[SPRITE_ANIMATION_ID].update(
		set_iter(system_manager->entities + SPRITE_ANIMATION_ID), 
		dt
	);
}

void system_manager_draw(SystemManager* system_manager, EntityPair* begin, EntityPair* end) {
	component_t* id = NULL;
	for (EntityPair* p = begin; p < end; p++) {
		SetIterator* iter = set_iter(system_manager->drawable_components + p->entity);
		while ((id = (component_t*)set_iter_next(iter)) != NULL) {
			system_manager->system[*id].draw(p->entity);
		}
	}
}

void system_manager_clear(SystemManager* system_manager) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		set_clear(system_manager->entities + i);
	}
	for (int i = 0; i < MAX_ENTITIES; i++) {
		set_clear(system_manager->drawable_components + i);
	}
}
