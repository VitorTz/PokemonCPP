#include <assert.h>
#include "ecs_manager.h"
#include "../util/avl_tree.h"


static avl_tree_t* ecs_map;
static ecs_t* ecs_instance;


static size_t hash_scene_id(const void* k) {
	const size_t h = (size_t) *((enum SceneID*)(k));
	return h;
}


void ecs_manager_init() {
	ecs_map = avl_tree_create(sizeof(ecs_t), hash_scene_id);
	ecs_instance = NULL;
}


void ecs_manager_close() {
	iterator_t iter = avl_tree_iter(ecs_map);
	for (ecs_t* ecs = iter.begin; ecs < iter.end; ecs++) {
		ecs_close(ecs);
	}
	avl_tree_destroy(ecs_map);
}


void ecs_manager_create_instance(const enum SceneID scene_id) {
	if (avl_tree_at(ecs_map, &scene_id) == NULL) {
		ecs_t ecs_;
		avl_tree_insert(ecs_map, &scene_id, &ecs_);
		ecs_t* ecs = (ecs_t*) avl_tree_at(ecs_map, &scene_id);
		ecs_init(ecs);
	}
}


void ecs_manager_set_instance(const enum SceneID scene_id) {
	ecs_instance = avl_tree_at(ecs_map, &scene_id);
	assert(ecs_instance != NULL);	
}


ecs_t* ecs_manager_get_instance() {
	return ecs_instance;
}


void ecs_manager_destroy_instance(const enum SceneID scene_id) {
	ecs_t* ecs = (ecs_t*)avl_tree_at(ecs_map, &scene_id);
	if (ecs != NULL) {
		ecs_close(ecs);
		avl_tree_erase(ecs_map, &scene_id);
	}
}


void ecs_manager_destroy_all_instances() {
	iterator_t iter = avl_tree_iter(ecs_map);
	for (ecs_t* ecs = iter.begin; ecs < iter.end; ecs++) {
		ecs_close(ecs);
	}
	avl_tree_clear(ecs_map);
}