#include "scene.h"


void scene_test_scene_init() {
	ecs_manager_create_instance(TestSceneID);
	ecs_manager_set_instance(TestSceneID);
	ecs_t* ecs = ecs_manager_get_instance();
	for (int i = 0; i < MAX_ENTITIES; i++) {
		const entity_t e = ecs_create_sprite(
			ecs, 
			0, 
			GRAPHICS_PATH "icons/Atrox.png",
			GetRandomValue(0, SCREEN_W),
			GetRandomValue(0, SCREEN_H)
		);		
	}
}


void scene_test_scene_update(const float dt) {
	ecs_manager_set_instance(TestSceneID);
	ecs_update(ecs_manager_get_instance(), dt);
}


void scene_test_scene_draw() {
	ecs_manager_set_instance(TestSceneID);
	ecs_draw(ecs_manager_get_instance());
}