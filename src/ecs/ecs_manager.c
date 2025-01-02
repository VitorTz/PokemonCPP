#include "ecs_manager.h"


static ECS* instances[NumScenes];
static SceneID current_scene_id = MAIN_SCENE;
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

ECS* ecs_manager_create_ecs_instance(const SceneID scene_id) {
	if (instances[scene_id] == NULL) {
		instances[scene_id] = ecs_create(scene_id);
	}
	return instances[scene_id];
}

void ecs_manager_destroy_ecs_instance(const SceneID scene_id) {
	if (instances[scene_id] != NULL) {
		ecs_destroy(instances[scene_id]);		
		instances[scene_id] = NULL;
		if (scene_id == current_scene_id) {
			ecs = NULL;
		}
	}
}

void ecs_manager_set_ecs_instance(const SceneID scene_id) {
	assert(instances[scene_id] != NULL);
	current_scene_id = scene_id;
	ecs = instances[scene_id];
}


ECS* ecs_manager_get_ecs_instance(const SceneID scene_id) {
	return instances[scene_id];
}

ECS* ecs_manager_get_current_ecs_instance() {
	return ecs;
}
