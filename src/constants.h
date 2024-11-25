#pragma once
#include <raylib.h>
#include "util/scene_id.h"


#define SCREEN_W 1280.0f
#define SCREEN_H 720.0f
#define SCREEN_CENTERX 640.0f
#define SCREEN_CENTERY 360.0f
#define WINDOW_TITLE "PokemonC"
#define FPS 60

#define RES "./resources/"
#define BACKGROUNDS_PATH "./resources/graphics/backgrounds/"
#define GRAPHICS_PATH "./resources/graphics/"
#define CHARACTERS_PATH "./resources/graphics/characters/"
#define MAPS_PATH "./resources/data/maps/"

#define MAX_ENTITIES 4096
#define MAIN_SCENE WorldSceneID

#define GAME_CHARACTER_SIZE 128.0f
#define TILE_SIZE 64.0f

#define PLAYER_SPEED 150.0f

#define DEBUG_MODE 1

#define CAMERA_ZINDEX_MIN 0
#define CAMERA_ZINDEX_MAX 6

#define SPRITE_ANIMATION_SPEED_SLOW 16
#define SPRITE_ANIMATION_SPEED_NORMAL 8
#define SPRITE_ANIMATION_SPEED_FAST 4

#define LEFT_KEY KEY_A
#define RIGHT_KEY KEY_D
#define UP_KEY KEY_W
#define DOWN_KEY KEY_S
#define ACTION_KEY KEY_F
