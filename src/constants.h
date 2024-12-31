#ifndef POKE_CONSTANTS_H
#define POKE_CONSTANTS_H
#include <raylib.h>
#include "util/types.h"


// Resources
#define ASSETS_PATH "./resources/"
#define GRAPHICS_PATH "./resources/graphics/"
#define ICONS_PATH "./resources/graphics/icons/"
#define MONSTERS_PATH "./resources/graphics/monsters/"
#define CHARACTERS_PATH "./resources/graphics/characters/"

// Window
#define SCREEN_W 1280
#define SCREEN_H 720
#define SCREEN_CENTERX 640
#define SCREEN_CENTERY 360
#define WINDOW_TITLE "Pokemon"
#define WINDOW_FPS 60

// Program
#define DEBUG_MODE 1

// Keyboard
#define POKE_LEFT_KEY KEY_A
#define POKE_RIGHT_KEY KEY_D
#define POKE_UP_KEY KEY_W
#define POKE_DOWN_KEY KEY_S

// Scenes
#define MAIN_SCENE TestScene1ID
#define  SCENE_TRANSITION_TIME 1.0f

// ECS
#define MAX_ENTITIES 4096
#define CHARACTER_SIZE 128.0f
#define TILE_SIZE 64.0f

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

#define CAMERA_ZOOM_MIN 0.5f
#define CAMERA_ZOOM_MAX 2.5f

// Sprite Animation
#define SPRITE_ANIMATION_SPEED_SLOW 12
#define SPRITE_ANIMATION_SPEED_NORMAL 8
#define SPRITE_ANIMATION_SPEED_FAST 4


#endif // !POKE_CONSTANTS_H