#pragma once
#include "../constants.h"
#include "../util/scene_id.h"
#include "../util/texture_pool.h"
#include "../ecs/ecs_manager.h"


typedef struct scene {
	void (*init)();
	void (*update)(float dt);
	void (*draw)();
} scene_t;


void scene_title_screen_init();
void scene_title_screen_update(float dt);
void scene_title_screen_draw();

void scene_world_init();
void scene_world_update(float dt);
void scene_world_draw();

void scene_fire_arena_init();
void scene_fire_arena_update(float dt);
void scene_fire_arena_draw();

void scene_plant_arena_init();
void scene_plant_arena_update(float dt);
void scene_plant_arena_draw();

void scene_water_arena_init();
void scene_water_arena_update(float dt);
void scene_water_arena_draw();

void scene_hospital_init();
void scene_hospital_update(float dt);
void scene_hospital_draw();

void scene_house_init();
void scene_house_update(float dt);
void scene_house_draw();

void scene_test_scene_init();
void scene_test_scene_update(float dt);
void scene_test_scene_draw();

void scene_manager_init();
void scene_manager_update(float dt);
void scene_manager_change_scene(enum SceneID sceneid);
void scene_manager_draw();
