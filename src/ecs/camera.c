#include "camera.h"
#include <assert.h>
#include <raymath.h>


void camera_init(camera_t* camera) {
	camera->camera2D = (Camera2D){
		(Vector2) {SCREEN_CENTERX, SCREEN_CENTERY },
		(Vector2) { SCREEN_CENTERX, SCREEN_CENTERY },
		0.0f,
		1.0f
	};
	camera->entities = (vector_t*)malloc(sizeof(vector_t) * CAMERA_ZINDEX_MAX + 1);
	assert(camera->entities);
	for (vector_t* v = camera->entities; v < camera->entities + CAMERA_ZINDEX_MAX + 1; v++) {
		vector_init(v, sizeof(entity_pair_t), MAX_ENTITIES / 4);
	}
	camera->size = 0;
	camera->is_on_camera = (uint8_t*)calloc(MAX_ENTITIES, sizeof(uint8_t));
	assert(camera->is_on_camera != NULL);
}

void camera_close(camera_t* camera) {
	if (camera == NULL) {
		return;
	}
	for (vector_t* v = camera->entities; v < camera->entities + CAMERA_ZINDEX_MAX + 1; v++) {
		vector_close(v);
	}
	free(camera->is_on_camera);
	free(camera->entities);
}

void camera_reset(camera_t* camera) {
	camera->camera2D = (Camera2D){
		(Vector2) { SCREEN_CENTERX, SCREEN_CENTERY },
		(Vector2) { SCREEN_CENTERX, SCREEN_CENTERY },
		0.0f,
		1.0f
	};
	camera_clear(camera);
}

void camera_insert(camera_t* camera, const entity_t e, const zindex_t zindex) {
	assert(zindex >= CAMERA_ZINDEX_MIN && zindex <= CAMERA_ZINDEX_MAX);
	if (camera->is_on_camera[e] == 0) {
		camera->is_on_camera[e] = 1;
		const entity_pair_t pair = { e, 0.0f };
		vector_t* vec = camera->entities + zindex;
		vector_push_back(vec, &pair);
		camera->size++;
	}
}

void camera_erase(camera_t* camera, const entity_t e, const zindex_t zindex) {
	assert(zindex >= CAMERA_ZINDEX_MIN && zindex <= CAMERA_ZINDEX_MAX);
	if (camera->is_on_camera[e] == 1) {
		camera->is_on_camera[e] = 0;
		size_t i = 0;
		vector_t* vec = camera->entities + zindex;		
		for (entity_pair_t* p = vector_begin(vec); p < vector_end(vec); p++) {
			if (p->entity == e) {
				vector_erase(vec, i);
				camera->size--;
				return;
			}
			i++;
		}
	}
}

float camera_get_zoom(const camera_t* camera) {
	return camera->camera2D.zoom;
}

void camera_set_zoom(camera_t* camera, const float zoom) {
	camera->camera2D.zoom = Clamp(zoom, CAMERA_ZOOM_MIN, CAMERA_ZOOM_MAX);
}

void camera_add_zoom(camera_t* camera, const float zoom) {
	camera->camera2D.zoom = Clamp(
		camera->camera2D.zoom + zoom,
		CAMERA_ZOOM_MIN,
		CAMERA_ZOOM_MAX
	);
}

void camera_set_target(camera_t* camera, const Vector2 target) {
	camera->camera2D.target = target;
}

Vector2 camera_get_target(const camera_t* camera) {
	return camera->camera2D.target;
}

void camera_begin_drawing(const camera_t* camera) {
	BeginDrawing(camera->camera2D);
}

void camera_end_drawing() {
	EndDrawing();
}

void camera_set_offset(camera_t* camera, const Vector2 offset) {
	camera->camera2D.offset = offset;
}

Vector2 camera_get_offset(const camera_t* camera) {
	return camera->camera2D.offset;
}

void camera_clear(camera_t* camera) {
	for (vector_t* v = camera->entities; v < camera->entities + CAMERA_ZINDEX_MAX + 1; v++) {
		vector_clear(v);		
	}
	for (uint8_t* p = camera->is_on_camera; p < camera->is_on_camera + MAX_ENTITIES; p++) {
		*p = 0;
	}
	camera->size = 0;
}

size_t camera_num_entities(const camera_t* camera) {
	return camera->size;
}
