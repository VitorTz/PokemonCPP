#include "system_manager.h"


static size_t hash_component(const void* k) {
	const component_t c = *((component_t*)(k));
	return c;
}

static size_t hash_entity(const void* k) {
	const entity_t e = *((entity_t*)(k));
	return e;
}


system_manager_t* system_manager_create() {
	system_manager_t* s = (system_manager_t*)malloc(sizeof(system_manager_t));
	assert(s != NULL);

	// Init systems
	s->systems[TRANSFORM_ID] = (system_t){ NULL, NULL };
	s->systems[SPRITE_ID] = (system_t){ NULL, system_sprite_draw };
	s->systems[SPRITE_ANIMATION_ID] = (system_t){ system_sprite_animation_update, system_sprite_animation_draw };
	s->systems[CHARACTER_ID] = (system_t){ system_character_update, NULL };
	s->systems[MOVEMENT_ID] = (system_t){ system_movement_update, NULL };
	s->systems[COAST_ID] = (system_t){ system_coast_update, system_coast_draw };
	s->systems[PLAYER_ID] = (system_t){ system_player_update, NULL };
	s->systems[WATER_ID] = (system_t){ system_water_update, system_water_draw };
	s->systems[TRANSITION_ID] = (system_t){ system_transition_update, system_transition_draw };
	system_coast_init();
	
	s->entities_set_by_component = (set_t*)malloc(sizeof(set_t) * NUM_COMPONENTS);
	s->drawable_components_by_entity = (set_t*)malloc(sizeof(set_t) * MAX_ENTITIES);
	s->drawable_components_set = set_create(sizeof(component_t), hash_component);
	
	// Create a set of entities for each component id
	for (int i = 0; i < NUM_COMPONENTS; i++)
		set_init(s->entities_set_by_component + i, sizeof(entity_t), hash_entity);

	// Create a set of drawable components ids for each entity
	for (int i = 0; i < MAX_ENTITIES; i++)
		set_init(s->drawable_components_by_entity + i, sizeof(component_t), hash_component);	

	// Register Drawable components	
	component_t id;
    id = SPRITE_ID; set_insert(s->drawable_components_set, &id);
	id = SPRITE_ANIMATION_ID; set_insert(s->drawable_components_set, &id);
	id = COAST_ID; set_insert(s->drawable_components_set, &id);
	id = WATER_ID; set_insert(s->drawable_components_set, &id);
	id = TRANSITION_ID; set_insert(s->drawable_components_set, &id);

	// Update Order
	s->update_order[0] = MOVEMENT_ID;
	s->update_order[1] = SPRITE_ANIMATION_ID;
	s->update_order[2] = CHARACTER_ID;
	s->update_order[3] = COAST_ID;
	s->update_order[4] = WATER_ID;
	s->update_order[5] = PLAYER_ID;
	s->update_order[6] = TRANSITION_ID;
	return s;
}


void system_manager_destroy(system_manager_t* s) {
	for (int i = 0; i < NUM_COMPONENTS; i++)
		set_close(s->entities_set_by_component + i);

	for (int i = 0; i < MAX_ENTITIES; i++)
		set_close(s->drawable_components_by_entity + i);

	set_destroy(s->drawable_components_set);
	free(s->entities_set_by_component);
	free(s->drawable_components_by_entity);
	free(s);
}


void system_manager_insert(system_manager_t* s, const entity_t e, const component_t id) {
	set_insert(s->entities_set_by_component + id, &e);
	if (set_contains(s->drawable_components_set, &id))
		set_insert(s->drawable_components_by_entity + e, &id);
}


void system_manager_erase(system_manager_t* s, const entity_t e, const component_t id) {
	set_erase(s->entities_set_by_component + id, &e);
	set_erase(s->drawable_components_by_entity + e, &id);
}


void system_manager_destroy_entity(system_manager_t* s, const entity_t e) {
	for (int i = 0; i < NUM_COMPONENTS; i++)
		set_erase(s->entities_set_by_component + i, &e);
	set_clear(s->drawable_components_by_entity + e);
}


void system_manager_update(system_manager_t* s, const float dt) {
	for (int i = 0; i < NUM_UPDATABLE_COMPONENTS; i++) {
		const component_t id = s->update_order[i];
		set_t* ent_set = s->entities_set_by_component + id;		
		s->systems[id].update(dt, set_iter(ent_set));		
	}
}


void system_manager_draw(system_manager_t* s, const iterator_t iter) {
	for (entity_pair_t* pair = iter.begin; pair < iter.end; pair++) {		
		const iterator_t s_iter = set_iter(s->drawable_components_by_entity + pair->e);
		for (component_t* id = s_iter.begin; id < s_iter.end; id++)
			s->systems[*id].draw(pair->e);
	}
}


void system_manager_clear(system_manager_t* s) {
	for (int i = 0; i < NUM_COMPONENTS; i++)
		set_clear(s->entities_set_by_component + i);
	for (int i = 0; i < MAX_ENTITIES; i++)
		set_clear(s->drawable_components_by_entity + i);
}