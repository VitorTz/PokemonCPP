#include "scene.h"
#include "../constants.h"

static Scene scene = { 0 };
static SceneID current_scene_id = MAIN_SCENE;
static SceneID next_scene_id = MAIN_SCENE;
static int should_change_scene = 0;


static void load_next_scene() {
	switch (next_scene_id) {
		case TitleScreenID:
			scene = (Scene){
				scene_title_screen_init,
				scene_title_screen_update,
				scene_title_screen_draw
			};
			break;
		case WorldSceneID:
			scene = (Scene){
				scene_world_init,
				scene_world_update,
				scene_world_draw
			};
			break;
		case FireArenaSceneID:
			scene = (Scene){
				scene_fire_arena_init,
				scene_fire_arena_update,
				scene_fire_arena_draw
			};
			break;
		case WaterArenaSceneID:
			scene = (Scene){
				scene_water_arena_init,
				scene_water_arena_update,
				scene_water_arena_draw
			};
			break;
		case PlantArenaSceneID:
			scene = (Scene){
				scene_plant_arena_init,
				scene_plant_arena_update,
				scene_plant_arena_draw
			};
			break;
		case HospitalSceneID:
			scene = (Scene){
				scene_hospital_init,
				scene_hospital_update,
				scene_hospital_draw
			};
			break;
		case HouseSceneID:
			scene = (Scene){
				scene_house_init,
				scene_house_update,
				scene_house_draw
			};
			break;
		case TestScene1ID:
			scene = (Scene){
				scene_test_1_init,
				scene_test_1_update,
				scene_test_1_draw
			};
			break;
		case TestScene2ID:
			scene = (Scene){
				scene_test_2_init,
				scene_test_2_update,
				scene_test_2_draw
			};
			break;
		case TestScene3ID:
			scene = (Scene){
				scene_test_3_init,
				scene_test_3_update,
				scene_test_3_draw
			};
			break;
		default:			
			break;
	}
	scene.init();
	current_scene_id = next_scene_id;	
}

void scene_manager_init() {
	load_next_scene();
}

void scene_manager_change_scene(const SceneID scene_id) {
	if (scene_id != current_scene_id) {
		should_change_scene = 1;
		next_scene_id = scene_id;
	}
}

void scene_manager_update(const float dt) {
	scene.update(dt);
}

void scene_manager_draw() {
	scene.draw();
	if (should_change_scene) {
		should_change_scene = 0;
		load_next_scene();
	}
}
