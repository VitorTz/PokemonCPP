#include <assert.h>
#include "system_manager.h"
#include "components.h"
#include "system_sprite.h"
#include "system_sprite_animation.h"
#include "../util/util.h"
#include "../constants.h"


void system_manager_init(system_manager_t* s) {
	s->system_arr = (system_t*)malloc(sizeof(system_t) * NUM_COMPONENTS);
	assert(s->system_arr != NULL);
	
	s->system_arr[TRANSFORM_ID].update = NULL;
	s->system_arr[TRANSFORM_ID].draw = NULL;
	
	s->system_arr[SPRITE_ID].update = NULL;
	s->system_arr[SPRITE_ID].draw = sprite_draw;
	
	s->system_arr[SPRITE_ANIMATION_ID].update = sprite_animation_update;
	s->system_arr[SPRITE_ANIMATION_ID].draw = sprite_animation_draw;


	// Component -> Entities
	s->component_to_entities = (set_t*)malloc(sizeof(set_t) * NUM_COMPONENTS);
	assert(s->component_to_entities != NULL);
	for (set_t* set = s->component_to_entities; set < s->component_to_entities + NUM_COMPONENTS; set++) {
		set_init(set, sizeof(entity_t), MAX_ENTITIES / 4, hash_entity_t);
	}

	// Entities -> Drawable Components
	s->entities_to_drawable_components = (set_t*)malloc(sizeof(set_t) * MAX_ENTITIES);
	assert(s->entities_to_drawable_components != NULL);
	for (set_t* set = s->entities_to_drawable_components; set < s->entities_to_drawable_components + MAX_ENTITIES; set++) {
		set_init(set, sizeof(component_t), NUM_DRAWABLE_COMPONENTS, hash_component_t);
	}
}

void system_manager_close(system_manager_t* s) {
	if (s == NULL) {
		return;
	}

	free(s->system_arr);

	// Component -> Entities
	for (set_t* set = s->component_to_entities; set < s->component_to_entities + NUM_COMPONENTS; set++) {
		set_close(set);		
	}
	free(s->component_to_entities);

	// Entities -> Drawable Components
	for (set_t* set = s->entities_to_drawable_components; set < s->entities_to_drawable_components + MAX_ENTITIES; set++) {
		set_close(set);
	}
	free(s->entities_to_drawable_components);
}

void system_manager_insert(system_manager_t* s, const entity_t e, const component_t id) {
	set_insert(s->component_to_entities + id, &e);
	if (component_is_drawable(id)) {
		set_insert(s->entities_to_drawable_components + e, &id);
	}	
}

void system_manager_erase(system_manager_t* s, const entity_t e, const component_t id) {
	set_erase(s->component_to_entities + id, &e);
	set_erase(s->entities_to_drawable_components + e, &id);
}

void system_manager_destroy_entity(system_manager_t* s, const entity_t e) {
	// Component -> Entities
	for (set_t* set = s->component_to_entities; set < s->component_to_entities + NUM_COMPONENTS; set++) {
		set_erase(set, &e);
	}

	// Entities -> Drawable Components
	set_clear(s->entities_to_drawable_components + e);
}

void system_manager_clear(system_manager_t* s) {
	// Component -> Entities
	for (set_t* set = s->component_to_entities; set < s->component_to_entities + NUM_COMPONENTS; set++) {
		set_clear(set);
	}

	// Entities -> Drawable Components
	for (set_t* set = s->entities_to_drawable_components; set < s->entities_to_drawable_components + MAX_ENTITIES; set++) {
		set_clear(set);
	}
}

set_iterator_t system_manager_entities_by_component(system_manager_t* s, const component_t id) {
	return set_iter(s->component_to_entities + id);
}
