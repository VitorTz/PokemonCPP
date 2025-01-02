#include "ecs_manager.h"


static ECS* instances[NumScenes];
static ECS* ecs = NULL;


void ecs_manager_init() {
	for (int i = 0; i < NumScenes; i++) {
		instances[i] = NULL;
	}
}

void ecs_manager_close() {
	for (int i = 0; i < NumScenes; i++) {
		if (instances[i] != NULL) {
			ecs_destroy(instances[i]);
			instances[i] = NULL;
		}		
	}
}

void ecs_manager_create_ecs_instance(const SceneID scene_id) {
	if (instances[scene_id] == NULL) {
		instances[scene_id] = ecs_create(scene_id);
	}
}

void ecs_manager_destroy_ecs_instance(const SceneID scene_id) {
	if (instances[scene_id] != NULL) {
		ecs_destroy(instances[scene_id]);		
		instances[scene_id] = NULL;
	}
}

void ecs_manager_set_ecs_instance(const SceneID scene_id) {
	assert(instances[scene_id] != NULL);
	ecs = instances[scene_id];
}

ECS* ecs_manager_get_ecs_instance() {
	return ecs;
}
