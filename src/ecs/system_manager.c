#include <assert.h>
#include "system_manager.h"
#include "components.h"
#include "../util/util.h"
#include "../constants.h"


void system_manager_init(system_manager_t* s) {
	s->system = (system_t*)malloc(sizeof(system_t) * NUM_COMPONENTS);
	assert(s->system != NULL);

	s->system[TRANSFORM_ID].update = NULL;
	s->system[TRANSFORM_ID].draw = NULL;
	
	s->system[SPRITE_ID].update = NULL;
	s->system[SPRITE_ID].draw = sprite_draw;

	s->system[SPRITE_ANIMATION_ID].update = sprite_animation_update;
	s->system[SPRITE_ANIMATION_ID].draw = sprite_animation_draw;

	// Components -> Entities
	s->entities = (set_t*)malloc(sizeof(set_t) * NUM_COMPONENTS);
	assert(s->entities != NULL);
	for (set_t* set = s->entities; set < s->entities + NUM_COMPONENTS; set++) {
		set_init(set, sizeof(entity_t), MAX_ENTITIES / 4, hash_component_t);
	}
	
	// Entities -> Drawable Components
	s->drawable_components = (vector_t*)malloc(sizeof(vector_t) * MAX_ENTITIES);
	assert(s->drawable_components != NULL);
	for (vector_t* v = s->drawable_components; v < s->drawable_components + MAX_ENTITIES; v++) {
		vector_init(v, sizeof(component_t), NUM_DRAWABLE_COMPONENTS);
	}
}

void system_manager_close(system_manager_t* s) {
	if (s == NULL) { return; }
	free(s->system);

	for (set_t* set = s->entities; set < s->entities + NUM_COMPONENTS; set++) {
		set_close(set);
	}
	free(s->entities);

	for (vector_t* v = s->drawable_components; v < s->drawable_components + MAX_ENTITIES; v++) {
		vector_close(v);
	}
	free(s->drawable_components);
}

void system_manager_insert(system_manager_t* s, const entity_t e, const component_t component_id) {
	set_insert(s->entities + component_id, &e);
	if (component_is_drawable(component_id)) {
		vector_push_back(s->drawable_components + e, &component_id);
	}
}

void system_manager_erase(system_manager_t* s, const entity_t e, const component_t component_id) {
	set_erase(s->entities + component_id, &e);
	vector_t* vec = s->drawable_components + e;
	component_t* begin = (component_t*)vector_begin(vec);
	component_t* end = (component_t*)vector_end(vec);
	size_t i = 0;
	for (component_t* id = begin; id < end; id++) {
		if (*id == component_id) {
			vector_erase(vec, i);
			return;
		}
		i++;
	}
}

void system_manager_destroy_entity(system_manager_t* s, const entity_t e) {
	for (set_t* set = s->entities; set < s->entities + NUM_COMPONENTS; set++) {
		set_erase(set, &e);
	}
	vector_clear(s->drawable_components + e);
}

void system_manager_update(system_manager_t* s, const component_t component_id, const float dt) {
;	set_t* set = s->entities + component_id;
	system_t* system = s->system + component_id;
	for (vector_t* vec = set_begin(set); vec < set_end(set); vec++) {
		entity_t* begin = (entity_t*)vector_begin(vec);
		entity_t* end = (entity_t*)vector_end(vec);
		system->update(begin, end, dt);
	}
}

void system_manager_draw(system_manager_t* s, entity_pair_t* begin, entity_pair_t* end) {
	for (entity_pair_t* p = begin; p < end; p++) {
		vector_t* vec = s->drawable_components + p->entity;
		component_t* begin = (component_t*)vector_begin(vec);
		component_t* end = (component_t*)vector_end(vec);
		for (component_t* id = begin; id < end; id++) {
			system_t* system = s->system + *id;
			system->draw(p->entity);
		}
	}
}

void system_manager_clear(system_manager_t* s) {
	for (set_t* set = s->entities; set < s->entities + NUM_COMPONENTS; set++) {
		set_clear(set);
	}
	for (vector_t* v = s->drawable_components; v < s->drawable_components + MAX_ENTITIES; v++) {
		vector_clear(v);
	}
}