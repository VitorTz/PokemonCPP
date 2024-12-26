#include "ecs_manager.h"


static ecs_t* ecs_instances[NumScenes];


void ecs_manager_init() {
	for (int i = 0; i < NumScenes; i++) {
		ecs_instances[i] = NULL;
	}
}

void ecs_manager_close() {
	for (int i = 0; i < NumScenes; i++) {
		ecs_destroy(ecs_instances[i]);
	}	
}

ecs_t* ecs_manager_get_instance(const SceneID scene_id) {
	return ecs_instances[scene_id];
}

void ecs_manager_create_intance(const SceneID scene_id) {
	if (ecs_instances[scene_id] != NULL) {
		ecs_instances[scene_id] = ecs_create(scene_id);
	}
}

void ecs_manager_destroy_instance(const SceneID scene_id) {
	ecs_destroy(ecs_instances[scene_id]);
}