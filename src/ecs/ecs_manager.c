#include "ecs_manager.h"


static ecs_t* ecs_instance_arr[NumScenes];
static ecs_t* ecs_instance = NULL;


void ecs_manager_init() {
	for (int i = 0; i < NumScenes; i++) {
		ecs_instance_arr[i] = NULL;
	}

}

void ecs_manager_close() {
	for (int i = 0; i < NumScenes; i++) {
		ecs_destroy(ecs_instance_arr[i]);
	}	
}

ecs_t* ecs_manager_get_instance(const SceneID scene_id) {
	return ecs_instance_arr[scene_id];
}

void ecs_manager_create_intance(const SceneID scene_id) {
	if (ecs_instance_arr[scene_id] == NULL) {
		ecs_instance_arr[scene_id] = ecs_create(scene_id);
	}
}

void ecs_manager_destroy_instance(const SceneID scene_id) {
	ecs_destroy(ecs_instance_arr[scene_id]);
}

void ecs_manager_set_current_ecs_instance(const SceneID scene_id) {
	ecs_instance = ecs_instance_arr[scene_id];
}

ecs_t* ecs_manager_get_current_ecs_instance() {
	return ecs_instance;
}
