#ifndef POKE_CONSTANTS_H
#define POKE_CONSTANTS_H
#include "scene/scene_id.h"


// Resources
#define ASSETS_PATH "./resources/"

// Window
#define SCREEN_W 1280
#define SCREEN_H 720
#define SCREEN_CENTERX 640.0f
#define SCREEN_CENTERY 360.0f
#define WINDOW_TITLE "PokemonC"
#define FPS 60

// Ecs
#define MAX_ENTITIES 2048

// Scenes
#define MAIN_SCENE TestSceneID
#define SCENE_TRANSITION_TIME 1.0f


// Camera
#define CAMERA_ZINDEX_MIN 0
#define CAMERA_ZINDEX_GROUND 0
#define CAMERA_ZINDEX_WATER 1
#define CAMERA_ZINDEX_SHADOW 2
#define CAMERA_ZINDEX_WORLD 3
#define CAMERA_ZINDEX_WORLD_TOP 4
#define CAMERA_ZINDEX_SKY 5
#define CAMERA_ZINDEX_OVERLAY 6
#define CAMERA_ZINDEX_MAX 6

#define CAMERA_ZOOM_MIN 0.25f
#define CAMERA_ZOOM_MAX 2.5f


#endif // POKE_CONSTANTS_H

