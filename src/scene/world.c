#include "scene.h"


void scene_world_init() {
	ecs_manager_create_instance(WorldSceneID);
	ecs_manager_set_instance(WorldSceneID);
	ecs_t* ecs = ecs_manager_get_instance();
	entity_t e = ecs_create_entity(ecs, 0, 1);
	sprite_t* sprite = (sprite_t*) ecs_component_insert(ecs, e, SPRITE_ID);
	sprite_init(sprite, CHARACTERS_PATH "player.png");
}


void scene_world_update(const float dt) {
	ecs_manager_set_instance(WorldSceneID);
	ecs_update(ecs_manager_get_instance(), dt);
}


void scene_world_draw() {
	ecs_manager_set_instance(WorldSceneID);
	ecs_draw(ecs_manager_get_instance());
}