#include "system_manager.h"
#include "../util/hash.h"



SystemManager* system_manager_create() {
	SystemManager* s = (SystemManager*)malloc(sizeof(SystemManager));
	assert(s != NULL);
	
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		set_init(s->entities + i, sizeof(entity_t), hash_component_id);
		s->is_drawable_component[i] = 0;
	}

	for (int i = 0; i < MAX_ENTITIES; i++) {
		set_init(s->drawable_components + i, sizeof(component_t), hash_entity_id);
	}
}

void system_manager_register_system(
	SystemManager* s,
	component_t id,
	void (*update)(set_iterator_t*, float),
	void (*draw)(entity_t)
) {
	s->system[id] = (System){ update, draw };
	if (draw != NULL) {
		s->is_drawable_component[id] = 1;
	}
}

void system_manager_destroy(SystemManager* s) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		set_close(s->entities + i);
	}

	for (int i = 0; i < MAX_ENTITIES; i++) {
		set_close(s->drawable_components + i);
	}
	free(s);
}

void system_manager_insert(SystemManager* s, const entity_t e, const component_t id) {
	set_insert(s->entities + id, &e);
	if (s->is_drawable_component[id]) {
		set_insert(s->drawable_components + e, &id);
	}
}

void system_manager_erase(SystemManager* s, const entity_t e, const component_t id) {
	set_erase(s->entities + id, &e);
	set_erase(s->drawable_components + e, &id);
}

void system_manager_destroy_entity(SystemManager* s, entity_t e) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		set_erase(s->entities + i, &e);
	}
	set_clear(s->drawable_components + e);
}

void system_manager_update(SystemManager* s, const float dt) {
	s->system[SPRITE_ANIMATION_ID].update(set_iter(s->entities + SPRITE_ANIMATION_ID), dt);
}

void system_manager_draw(SystemManager* s, EntityPair* begin, EntityPair* end) {
	for (EntityPair* p = begin; p < end; p++) {
		set_iterator_t* iter = set_iter(s->drawable_components + p->entity);
		component_t* id;
		while ((id = (component_t*)set_iter_next(iter)) != NULL) {
			s->system[*id].draw(p->entity);
		}
	}
}

void system_manager_clear(SystemManager* s) {
	for (int i = 0; i < NUM_COMPONENTS; i++) {
		set_clear(s->entities + i);
	}
	for (int i = 0; i < MAX_ENTITIES; i++) {
		set_clear(s->drawable_components + i);
	}
}