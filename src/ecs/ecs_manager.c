#include "ecs_manager.h"


static ECS* instances[NumScenes];
static ECS* ecs;


void ecs_manager_init() {
	for (int i = 0; i < NumScenes; i++) {
		instances[i] = NULL;
	}
}

void ecs_manager_close() {
	for (int i = 0; i < NumScenes; i++) {
		if (instances[i] != NULL) {
			ecs_close(instances[i]);
		}		
	}
}

void ecs_manager_create_ecs_instance(const SceneID scene_id) {
	if (instances[scene_id] == NULL) {
		instances[scene_id] = (ECS*) malloc(sizeof(ECS));
		assert(instances[scene_id] != NULL);
		ecs_init(instances[scene_id]);
	}
}

void ecs_manager_set_ecs_instance(const SceneID scene_id) {
	ecs = instances[scene_id];
}

ECS* ecs_manager_get_ecs_instance() {
	return ecs;
}