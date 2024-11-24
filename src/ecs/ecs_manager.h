#pragma once
#include "ecs.h"
#include "../util/scene_id.h"

void ecs_manager_init();

void ecs_manager_close();

void ecs_manager_create_instance(enum SceneID scene_id);

void ecs_manager_set_instance(enum SceneID scene_id);

ecs_t* ecs_manager_get_instance();

void ecs_manager_destroy_instance(enum SceneID scene_id);

void ecs_manager_destroy_all_instances();
