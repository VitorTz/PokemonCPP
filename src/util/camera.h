#ifndef POKE_CAMERA_H
#define POKE_CAMERA_H
#include <raylib.h>
#include <assert.h>
#include "vector.h"
#include "../constants.h"


typedef struct _camera {
	Camera2D camera2D;
	size_t size;
	Vector zindex[CAMERA_ZINDEX_MAX + 1];
	int8_t is_on_camera[MAX_ENTITIES];
	Vector2 horizontal_limit;
	Vector2 vertical_limit;
	entity_t target_entity;
	int have_target;
} PokeCamera;


PokeCamera* camera_create();

void camera_destroy(const PokeCamera* camera);

void camera_insert(PokeCamera* camera, entity_t e, zindex_t zindex);

void camera_erase(PokeCamera* camera, entity_t e, zindex_t zindex);

void camera_clear(PokeCamera* camera);

void camera_add_zoom(PokeCamera* camera, float zoom);

void camera_set_zoom(PokeCamera* camera, float zoom);

void camera_set_target(PokeCamera* camera, float x, float y);

void camera_handle_zoom(PokeCamera* camera, float dt);

void camera_begin_drawing(const PokeCamera* camera);

void camera_end_drawing();

void camera_set_target_entity(PokeCamera* camera, entity_t e);

void camera_set_horizontal_limit(PokeCamera* camera, float min_left, float max_right);

void camera_set_vertical_limit(PokeCamera* camera, float min_top, float min_bottom);


#endif // !POKE_CAMERA_H
