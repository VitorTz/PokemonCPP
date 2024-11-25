#pragma once
#include <stdio.h>
#include <assert.h>
#include "ObjectGroupID.h"
#include "ObjectID.h"
#include "CharacterID.h"
#include "tile.h"
#include "../constants.h"
#include "../ecs/ecs.h"
#include "map_info.h"


void load_tiledmap(ecs_t* ecs, const char* file);

const map_info_t* get_map_info(enum SceneID scene_id);