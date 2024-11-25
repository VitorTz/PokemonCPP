#include "camera.h"


camera_t* camera_create() {
	camera_t* camera = (camera_t*) malloc(sizeof(camera_t));
	camera->camera2D = (Camera2D){
		(Vector2){SCREEN_CENTERX, SCREEN_CENTERY},
		(Vector2){SCREEN_CENTERX, SCREEN_CENTERY},
		0.0f,
		1.0f
	};
	camera->size = 0;
	camera->entities = (vector_t*)malloc(sizeof(vector_t) * CAMERA_ZINDEX_MAX);
	for (int i = 0; i < CAMERA_ZINDEX_MAX; i++) {
		vector_init(camera->entities + i, sizeof(entity_pair_t), MAX_ENTITIES / 4);
	}
	for (int i = 0; i < MAX_ENTITIES; i++) {
		camera->on_camera[i] = '0';
	}
	return camera;
}


void camera_destroy(camera_t* camera) {
	for (int i = 0; i < CAMERA_ZINDEX_MAX; i++) {
		vector_close(camera->entities + i);
	}
	free(camera->entities);
	free(camera);
}


void camera_insert(camera_t* camera, const entity_t e, const zindex_t z) {
	assert(z >= CAMERA_ZINDEX_MIN && z < CAMERA_ZINDEX_MAX);
	if (camera->on_camera[e] == '0') {
		camera->on_camera[e] = '1';
		vector_t* v = camera->entities + z;
		entity_pair_t pair = { 0.0f, e };
		vector_push_back(v, &pair);
		camera->size++;
	}
}


void camera_erase(camera_t* camera, const entity_t e, const zindex_t z) {
	assert(z >= CAMERA_ZINDEX_MIN && z < CAMERA_ZINDEX_MAX);
	if (camera->on_camera[e] == '1') {
		camera->on_camera[e] = '0';
		vector_t* v = camera->entities + z;
		size_t i = 0;
		iterator_t iter = vector_iter(v);
		for (entity_pair_t* pair = iter.begin; pair < iter.end; pair++) {
			if (pair->e == e) {
				vector_erase(v, i);
				camera->size--;
				return;
			}
			i++;
		}		
	}
}


void camera_clear(camera_t* camera) {
	for (int i = 0; i < CAMERA_ZINDEX_MAX; i++) {
		vector_clear(camera->entities + i);
	}
	camera->size = 0;
	for (int i = 0; i < MAX_ENTITIES; i++) {
		camera->on_camera[i] = '0';
	}
}


size_t camera_size(camera_t* camera) {
	return camera->size;
}