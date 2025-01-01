#ifndef POKE_SCENE_H
#define POKE_SCENE_H
#include "../util/types.h"


typedef struct _scene {
	void (*init)();
	void (*update)(float);
	void (*draw)();
} Scene;


void scene_manager_init();
void scene_manager_change_scene(SceneID scene_id);
void scene_manager_update(float dt);
void scene_manager_draw();

void scene_title_screen_init();
void scene_title_screen_update();
void scene_title_screen_draw();

void scene_world_init();
void scene_world_update();
void scene_world_draw();

void scene_fire_arena_init();
void scene_fire_arena_update();
void scene_fire_arena_draw();

void scene_water_arena_init();
void scene_water_arena_update();
void scene_water_arena_draw();

void scene_plant_arena_init();
void scene_plant_arena_update();
void scene_plant_arena_draw();

void scene_hospital_init();
void scene_hospital_update();
void scene_hospital_draw();

void scene_house_init();
void scene_house_update();
void scene_house_draw();

void scene_test_1_init();
void scene_test_1_update();
void scene_test_1_draw();

void scene_test_2_init();
void scene_test_2_update();
void scene_test_2_draw();

void scene_test_3_init();
void scene_test_3_update();
void scene_test_3_draw();



#endif // !POKE_SCENE_H
