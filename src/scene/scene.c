#include <raylib.h>
#include <raymath.h>
#include "scene.h"
#include "../util/config.h"
#include "../constants.h"


static scene_t scene = { 0 };
static SceneID current_scene_id = MAIN_SCENE;
static SceneID next_scene_id = MAIN_SCENE;

static int is_changing_scene = 0;
static int transition_is_fading_to_black = 0;
static Color transition_color = { 0, 0, 0, 0 };
static float transition_time = 0.0f;


static void scene_load_next_scene() {
	switch (next_scene_id) {
	case TitleScreenID:
		scene = (scene_t){
			scene_title_screen_init,
			scene_title_screen_update,
			scene_title_screen_draw
		};
		break;
	case WorldSceneID:
		scene = (scene_t){
			scene_world_init,
			scene_world_update,
			scene_world_draw
		};
		break;
	case FireArenaSceneID:
		scene = (scene_t){
			scene_fire_arena_init,
			scene_fire_arena_update,
			scene_fire_arena_draw
		};
		break;
	case PlantArenaSceneID:
		scene = (scene_t){
			scene_plant_arena_init,
			scene_plant_arena_update,
			scene_plant_arena_draw
		};
		break;
	case WaterArenaSceneID:
		scene = (scene_t){
			scene_water_arena_init,
			scene_water_arena_update,
			scene_water_arena_draw
		};
		break;
	case HospitalSceneID:
		scene = (scene_t){
			scene_hospital_init,
			scene_hospital_update,
			scene_hospital_draw
		};
		break;
	case HouseSceneID:
		scene = (scene_t){
			scene_house_init,
			scene_house_update,
			scene_house_draw
		};
		break;
	case TestSceneID:
		scene = (scene_t){
			scene_test_init,
			scene_test_update,
			scene_test_draw
		};
		break;
	default:
		break;
	}
	scene.init();
	current_scene_id = next_scene_id;
}

void scene_init() {
	scene_load_next_scene();
}

void scene_change(const SceneID scene_id) {
	is_changing_scene = 1;
	transition_time = 0.0f;
	next_scene_id = scene_id;
	transition_is_fading_to_black = 1;
	poke_config_set_should_clear_background(0);
}

void scene_update(const float dt) {
	if (!is_changing_scene) {
		scene.update(dt);
		return;
	}

	transition_time += dt;
	const float t = fminf(transition_time / SCENE_TRANSITION_TIME, 1.0f);
	transition_color.a = (unsigned char)transition_is_fading_to_black ? Lerp(0.0f, 255.f, t) : Lerp(255.f, 0.0f, t);

	if (transition_is_fading_to_black) {
		if (t == 1.0f) {
			transition_time = 0.0f;
			transition_is_fading_to_black = 0;
			scene_load_next_scene();
			is_changing_scene = 0;
			poke_config_set_should_clear_background(1);
		}
	}
}

void scene_draw() {
	if (!is_changing_scene) {
		scene.draw();
	}
	else {
		DrawRectangle(0, 0, SCREEN_W, SCREEN_H, transition_color);
	}
}