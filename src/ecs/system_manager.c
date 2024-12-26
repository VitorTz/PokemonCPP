#include "system_manager.h"
#include "system_sprite.h"
#include "system_sprite_animation.h"


const static component_t DRAWABLE_COMPONENTS_ARR[NUM_COMPONENTS] = {
	0,
	1,
	1
};

const static component_t UPDATE_ORDER[NUM_UPDATABLE_COMPONENTS] = {
	SPRITE_ANIMATION_ID
};


void system_manager_init(system_manager_t* s) {
	s->system[TRANSFORM_ID] = (system_t){ NULL, NULL };
	s->system[SPRITE_ID] = (system_t){ NULL, sprite_draw };
	s->system[SPRITE_ANIMATION_ID] = (system_t){ sprite_animation_update, sprite_animation_draw };


	// Component -> Entities (hash set)
	s->component_to_entities = (hash_set_t*)malloc(sizeof(hash_set_t) * NUM_COMPONENTS);
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_set_init(
			s->component_to_entities + i, 
			sizeof(entity_t), 
			MAX_ENTITIES / 4, 
			hash_component_t, 
			equal_entity_t
		);
	}

	// Entities -> Drawable Component (hash set)
	s->entities_to_drawable_components = (hash_set_t*)malloc(sizeof(hash_set_t) * MAX_ENTITIES);
	for (int i = 0; i < MAX_ENTITIES; i++) {
		hash_set_init(
			s->entities_to_drawable_components + i,
			sizeof(component_t),
			NUM_DRAWABLE_COMPONENTS,
			hash_entity_t,
			equal_component_t
		);
	}
}

void system_manager_close(system_manager_t* s) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_set_close(s->component_to_entities + i);
	}
	for (int i = 0; i < MAX_ENTITIES; i++) {
		hash_set_close(s->entities_to_drawable_components + i);
	}
	free(s->entities_to_drawable_components);
	free(s->component_to_entities);
}

void system_manager_insert(
	system_manager_t* s,
	const entity_t e,
	const component_t id
) {
	hash_set_insert(s->component_to_entities + id, &e);
	if (DRAWABLE_COMPONENTS_ARR[id]) {
		hash_set_insert(s->entities_to_drawable_components + e, &id);
	}
}

void system_manager_erase(
	system_manager_t* s,
	const entity_t e,
	const component_t id
) {
	hash_set_erase(s->component_to_entities + id, &e);	
	hash_set_erase(s->entities_to_drawable_components + e, &id);
}

void system_manager_entity_destroy(
	system_manager_t* s,
	const entity_t e
) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		hash_set_erase(s->component_to_entities + i, &e);
	}
	hash_set_clear(s->entities_to_drawable_components + e);
}

void system_manager_update(
	system_manager_t* s,
	const float dt
) {
	for (int i = 0; i < NUM_UPDATABLE_COMPONENTS; i++) {
		const component_t id = UPDATE_ORDER[i];
		system_t* system = &s->system[id];
		iterator_t iter = hash_set_iter(s->component_to_entities + id);
		system->update(&iter, dt);
	}
}

void system_manager_draw(system_manager_t* s) {

}
