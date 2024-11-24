#pragma once
#include <raylib.h>
#include "../util/scene_id.h"


typedef struct transition {
	enum SceneID scene_id;
	Rectangle rect;
} transition_t;