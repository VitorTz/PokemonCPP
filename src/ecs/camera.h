#pragma once
#include <raylib.h>
#include <assert.h>
#include "../constants.h"
#include "../util/vector.h"
#include "../util/types.h"
#include "../util/entity_pair.h"



typedef struct camera {
	Camera2D camera2D;
	vector_t* entities;
	char on_camera[MAX_ENTITIES];
	size_t size;
} camera_t;


camera_t* camera_create();

void camera_destroy(camera_t* camera);

void camera_insert(camera_t* camera, entity_t e, zindex_t z);

void camera_erase(camera_t* camera, entity_t e, zindex_t z);

void camera_clear(camera_t* camera);

size_t camera_size(camera_t* camera);