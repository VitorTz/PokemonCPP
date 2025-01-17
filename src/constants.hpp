#pragma once
#include <raylib.h>
#include "util/types.hpp"
#include "scene/SceneID.hpp"


#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION "330"
    #define SHADERS_PATH "./resources/shaders/glsl330/"
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION "100"
    #define SHADERS_PATH "./resources/shaders/glsl100/"
#endif


#define ASSETS_PATH "./resources/"
#define GRAPHICS_PATH "./resources/graphics/"
#define CHARACTERS_PATH "./resources/graphics/characters/"
#define ICONS_PATH "./resources/graphics/icons/"
#define UI_PATH "./resources/graphics/ui/"
#define MAPS_PATH "./resources/data/maps/"
#define AUDIO_PATH "./resources/audio"
#define TILE_SETS_PATH "./resources/graphics/tilesets/"


namespace pk {
    
    // Window
    constexpr int SCREEN_WIDTH{1280};
    constexpr int SCREEN_HEIGHT{720};
    constexpr char WINDOW_TITLE[]{"Pokemon"};
    constexpr int FPS{60};
    constexpr Vector2 SCREEN_SIZE{
        static_cast<float>(pk::SCREEN_WIDTH), 
        static_cast<float>(pk::SCREEN_HEIGHT)
    };
    constexpr Vector2 SCREEN_CENTER{
        static_cast<float>(pk::SCREEN_WIDTH) / 2.0f, 
        static_cast<float>(pk::SCREEN_HEIGHT) / 2.0f
    };
    constexpr bool DEBUG_MODE{true};

    // Scene
    constexpr pk::SceneID MAIN_SCENE{pk::TestScene1ID};

    // Ecs
    constexpr pk::entity_t MAX_ENTITIES{4096};    

    // Camera
    constexpr pk::zindex_t CAMERA_ZINDEX_MIN{0};
        constexpr pk::zindex_t CAMERA_ZINDEX_WATER{0};
        constexpr pk::zindex_t CAMERA_ZINDEX_GROUND{1};
        constexpr pk::zindex_t CAMERA_ZINDEX_COAST{2};
        constexpr pk::zindex_t CAMERA_ZINDEX_SHADOW{3};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD{4};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD_TOP{5};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD_SKY{6};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD_OVERLAY{7};
    constexpr pk::zindex_t CAMERA_ZINDEX_MAX{8};

    constexpr float CAMERA_ZOOM_MIN{0.25f};
    constexpr float CAMERA_ZOOM_MAX{2.5f};

    // Keyboard
    constexpr int KEY_MOVE_LEFT{KEY_A};
    constexpr int KEY_MOVE_RIGHT{KEY_D};
    constexpr int KEY_MOVE_UP{KEY_W};
    constexpr int KEY_MOVE_DOWN{KEY_S};

    // Sprite Animation Speed
    constexpr std::uint8_t SPRITE_ANIMATION_SPEED_SLOW{12};
    constexpr std::uint8_t SPRITE_ANIMATION_SPEED_NORMAL{8};
    constexpr std::uint8_t SPRITE_ANIMATION_SPEED_FAST{4};

    // Characters
    constexpr float CHARACTER_SIZE{128.0f};

    // Player
    constexpr float PLAYER_SPEED{150.0f};
    constexpr Rectangle PLAYER_COLLISION_RECT{
        0.0f,
        0.0f,
        CHARACTER_SIZE * 0.4,
        CHARACTER_SIZE * 0.4
    };

    constexpr pk::SpriteAnimationSource PLAYER_SPRITE_ANIMATION{
        pk::SpriteSheet{
            CHARACTERS_PATH "player.png",
            CHARACTER_SIZE,
            CHARACTER_SIZE,
            4,
            4
        },
        SPRITE_ANIMATION_SPEED_NORMAL
    };

    // Map
    constexpr float TILE_SIZE{64.0f};
    constexpr const char* MAP_PATH_BY_SCENE_ID[pk::NumScenes] {
        "null",
        MAPS_PATH "world.txt",
        MAPS_PATH "fire.txt",
        MAPS_PATH "plant.txt",
        MAPS_PATH "water.txt",
        MAPS_PATH "hospital.txt",
        MAPS_PATH "house.txt",
        "null",
        MAPS_PATH "world.txt"
    };


}