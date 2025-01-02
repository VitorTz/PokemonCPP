#ifndef POKE_ECS_MANAGER_H
#define POKE_ECS_MANAGER_H
#include "../util/types.h"
#include "ecs.h"


void ecs_manager_init();

void ecs_manager_close();

ECS* ecs_manager_create_ecs_instance(SceneID scene_id);

void ecs_manager_destroy_ecs_instance(SceneID scene_id);

void ecs_manager_set_ecs_instance(SceneID scene_id);

ECS* ecs_manager_get_ecs_instance(SceneID scene_id);

ECS* ecs_manager_get_current_ecs_instance();


#endif // !POKE_ECS_MANAGER_H
