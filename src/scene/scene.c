#include "scene.h"


static scene_t scenes[NumScenes];
static enum SceneID current_scene_id;
static enum SceneID next_scene_id;
static int should_change_scene;


void scene_manager_init() {
	scenes[TitleScreenID] = (scene_t){ 
		scene_title_screen_init, 
		scene_title_screen_update, 
		scene_title_screen_draw 
	};

	scenes[WorldSceneID] = (scene_t){
		scene_world_init,
		scene_world_update,
		scene_world_draw
	};

	scenes[FireArenaSceneID] = (scene_t){
		scene_fire_arena_init,
		scene_fire_arena_update,
		scene_fire_arena_draw
	};

	scenes[PlantArenaSceneID] = (scene_t){
		scene_plant_arena_init,
		scene_plant_arena_update,
		scene_plant_arena_draw
	};

	scenes[WaterArenaID] = (scene_t){
		scene_water_arena_init,
		scene_water_arena_update,
		scene_water_arena_draw
	};

	scenes[HospitalSceneID] = (scene_t){
		scene_hospital_init,
		scene_hospital_update,
		scene_hospital_draw
	};

	scenes[HouseSceneID] = (scene_t){
		scene_house_init,
		scene_house_update,
		scene_house_draw
	};

	scenes[TestSceneID] = (scene_t){
		scene_test_scene_init,
		scene_test_scene_update,
		scene_test_scene_draw
	};
	
	current_scene_id = next_scene_id = MAIN_SCENE;
	should_change_scene = 0;
	scenes[current_scene_id].init();
}


void scene_manager_change_scene(const enum SceneID sceneid) {
	should_change_scene = 1;
	next_scene_id = sceneid;
}


void scene_manager_update(const float dt) {
	scenes[current_scene_id].update(dt);	
}


void scene_manager_draw() {
	scenes[current_scene_id].draw();
	if (should_change_scene) {
		should_change_scene = 0;
		scenes[next_scene_id].init();
		current_scene_id = next_scene_id;
	}
}