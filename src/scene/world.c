#include "scene.h"
#include "../util/tiled_map.h"


void scene_world_init() {
	ecs_manager_create_instance(WorldSceneID);
	ecs_manager_set_instance(WorldSceneID);
	ecs_t* ecs = ecs_manager_get_instance();
	ecs_create_sprite(ecs, 0, MAPS_PATH "world.png", 0.0f, 0.0f);
	load_tiledmap(ecs, MAPS_PATH "world.txt");	
}


void scene_world_update(const float dt) {
	ecs_manager_set_instance(WorldSceneID);
	ecs_update(ecs_manager_get_instance(), dt);
}


void scene_world_draw() {
	ecs_manager_set_instance(WorldSceneID);
	ecs_draw(ecs_manager_get_instance());
}