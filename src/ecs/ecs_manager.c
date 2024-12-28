#include "ecs_manager.h"

static ecs_t* instances[NumScenes];
static ecs_t* current_instance;


void ecs_manager_init() {
	for (int i = 0; i < NumScenes; i++) {
		instances[i] = NULL;
	}
}

void ecs_manager_close() {
	for (int i = 0; i < NumScenes; i++) {
		if (instances[i] != NULL) {
			ecs_close(instances[i]);
			free(instances[i]);
			instances[i] = NULL;
		}
	}
}

void ecs_manager_create_ecs_instance(const SceneID scene_id) {
	if (instances[scene_id] == NULL) {
		instances[scene_id] = (ecs_t*)malloc(sizeof(ecs_t));
		ecs_init(instances[scene_id]);
	}
}

void ecs_manager_destroy_ecs_instance(const SceneID scene_id) {
	if (instances[scene_id] != NULL) {
		ecs_close(instances[scene_id]);
		free(instances[scene_id]);
		instances[scene_id] = NULL;
	}
}

void ecs_manager_set_current_ecs_instance(const SceneID scene_id) {
	current_instance = instances[scene_id];
}

ecs_t* ecs_manager_get_ecs_instance(const SceneID scene_id) {
	return instances[scene_id];
}

ecs_t* ecs_manager_get_current_ecs_instance() {
	return current_instance;
}
