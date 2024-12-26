#ifndef POKE_SCENE_H
#define POKE_SCENE_H
#include "scene_id.h"


typedef struct scene {
	void (*init)();
	void (*update)(float);
	void (*draw)();
} scene_t;


void scene_init();
void scene_update(float dt);
void scene_change(SceneID scene_id);
void scene_draw();

// TitleScreen
void scene_title_screen_init();
void scene_title_screen_update(float dt);
void scene_title_screen_draw();

// WorldScene
void scene_world_init();
void scene_world_update(float dt);
void scene_world_draw();

// FireArena
void scene_fire_arena_init();
void scene_fire_arena_update(float dt);
void scene_fire_arena_draw();

// PlantArena
void scene_plant_arena_init();
void scene_plant_arena_update(float dt);
void scene_plant_arena_draw();

// WaterArena
void scene_water_arena_init();
void scene_water_arena_update(float dt);
void scene_water_arena_draw();

// Hospital
void scene_hospital_init();
void scene_hospital_update(float dt);
void scene_hospital_draw();

// House
void scene_house_init();
void scene_house_update(float dt);
void scene_house_draw();

// TestScene
void scene_test_init();
void scene_test_update(float dt);
void scene_test_draw();


#endif