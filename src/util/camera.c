#include "camera.h"
#include <raymath.h>


PokeCamera* camera_create() {
	PokeCamera* camera = (PokeCamera*)malloc(sizeof(PokeCamera));
	assert(camera != NULL);
	camera->camera2D = (Camera2D){
		(Vector2) { SCREEN_CENTERX, SCREEN_CENTERY },
		(Vector2) { SCREEN_CENTERX, SCREEN_CENTERY },
		0.0f, 
		1.0f
	};
	for (int i = CAMERA_ZINDEX_MIN; i <= CAMERA_ZINDEX_MAX; i++) {
		vector_init(camera->zindex + i, sizeof(EntityPair), MAX_ENTITIES);
	}
	for (int i = 0; i < MAX_ENTITIES; i++) {
		camera->is_on_camera[i] = 0;
	}
	camera->horizontal_limit = (Vector2){ -SCREEN_W, SCREEN_W };
	camera->vertical_limit = (Vector2){ -SCREEN_H, SCREEN_H };
	camera->size = 0;
	return camera;
}

void camera_destroy(PokeCamera* camera) {
	for (int i = CAMERA_ZINDEX_MIN; i <= CAMERA_ZINDEX_MAX; i++) {
		vector_close(camera->zindex + i);
	}
}

void camera_insert(PokeCamera* camera, const entity_t e, const zindex_t z) {
	if (camera->is_on_camera[e] == 0) {
		camera->is_on_camera[e] = 1;
		const EntityPair p = { e, 0.0f };
		vector_push_back(camera->zindex + z, &p);
		camera->size++;
	}
}

void camera_erase(PokeCamera* camera, const entity_t e, const zindex_t z) {
	if (camera->is_on_camera[e] == 1) {
		camera->is_on_camera[e] = 0;
		size_t i = 0;
		Vector* v = camera->zindex + z;
		EntityPair* begin = (EntityPair*)vector_begin(v);
		EntityPair* end = (EntityPair*)vector_end(v);
		for (EntityPair* p = begin; p < end; p++) {
			if (p->entity == e) {
				vector_erase(v, i);
				camera->size--;
				return;
			}
			i++;
		}
	}
}

void camera_clear(PokeCamera* camera) {
	for (int i = CAMERA_ZINDEX_MIN; i <= CAMERA_ZINDEX_MAX; i++) {
		vector_clear(camera->zindex + i);
	}
	for (int i = 0; i < MAX_ENTITIES; i++) {
		camera->is_on_camera[i] = 0;
	}
	camera->size = 0;
}

void camera_add_zoom(PokeCamera* camera, const float zoom) {
	camera->camera2D.zoom = Clamp(
		camera->camera2D.zoom + zoom,
		CAMERA_ZOOM_MIN,
		CAMERA_ZOOM_MAX
	);
}

void camera_set_zoom(PokeCamera* camera, const float zoom) {
	camera->camera2D.zoom = Clamp(
		zoom,
		CAMERA_ZOOM_MIN,
		CAMERA_ZOOM_MAX
	);
}

void camera_handle_zoom(PokeCamera* camera, const float dt) {
	camera_add_zoom(camera, GetMouseWheelMove() * 2.0f * dt);
}

void camera_set_target(PokeCamera* camera, const float x, const float y) {
	camera->camera2D.target.x = Clamp(x, camera->horizontal_limit.x, camera->horizontal_limit.y);
	camera->camera2D.target.y = Clamp(y, camera->vertical_limit.x, camera->vertical_limit.y);
}

void camera_begin_drawing(PokeCamera* camera) {
	BeginMode2D(camera->camera2D);
}

void camera_end_drawing() {
	EndMode2D();
}

void camera_set_horizontal_limit(PokeCamera* camera, const float min_left, const float max_right) {
	camera->horizontal_limit.x = min_left;
	camera->horizontal_limit.y = max_right;
}

void camera_set_vertical_limit(PokeCamera* camera, const float min_top, const float min_bottom) {
	camera->vertical_limit.x = min_top;
	camera->vertical_limit.y = min_bottom;
}