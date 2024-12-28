#ifndef POKE_CAMERA_H
#define POKE_CAMERA_H
#include <stdlib.h>
#include <raylib.h>
#include <assert.h>
#include <raymath.h>
#include "../util/types.h"
#include "../util/vector.h"
#include "../util/entity_pair.h"
#include "../constants.h"


typedef struct camera {
	Camera2D camera2D;
	vector_t* entities;
	uint8_t* is_on_camera;
	size_t size;
} camera_t;


void camera_init(camera_t* camera);

void camera_close(camera_t* camera);

void camera_reset(camera_t* camera);

void camera_insert(camera_t* camera, entity_t e, zindex_t zindex);

void camera_erase(camera_t* camera, entity_t e, zindex_t zindex);

float camera_get_zoom(const camera_t* camera);

void camera_set_zoom(camera_t* camera, float zoom);

void camera_add_zoom(camera_t* camera, float zoom);

void camera_set_target(camera_t* camera, Vector2 target);

Vector2 camera_get_target(const camera_t* camera);

void camera_begin_drawing(const camera_t* camera);

void camera_end_drawing();

void camera_set_offset(camera_t* camera, Vector2 offset);

Vector2 camera_get_offset(const camera_t* camera);

void camera_clear(camera_t* camera);

size_t camera_num_entities(const camera_t* camera);


#endif // !POKE_CAMERA_H
