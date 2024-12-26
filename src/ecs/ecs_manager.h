#ifndef POKE_ECS_MANAGER_H
#define POKE_ECS_MANAGER_H
#include "ecs.h"


void ecs_manager_init();

void ecs_manager_close();

ecs_t* ecs_manager_get_instance(SceneID scene_id);

void ecs_manager_create_intance(SceneID scene_id);

void ecs_manager_destroy_instance(SceneID scene_id);


#endif