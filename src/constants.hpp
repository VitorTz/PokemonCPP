#pragma once
#include <raylib.h>
#include "util/types.hpp"
#include "scene/SceneID.hpp"


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

    // Scene
    constexpr pk::SceneID MAIN_SCENE{pk::TitleScreenID};

    // Ecs
    constexpr pk::entity_t MAX_ENTITIES{4096};    

    // Camera
    constexpr pk::zindex_t CAMERA_ZINDEX_MIN{0};
        constexpr pk::zindex_t CAMERA_ZINDEX_GROUND{0};
        constexpr pk::zindex_t CAMERA_ZINDEX_WATER{1};
        constexpr pk::zindex_t CAMERA_ZINDEX_SHADOW{2};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD{3};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD_TOP{4};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD_SKY{5};
        constexpr pk::zindex_t CAMERA_ZINDEX_WORLD_OVERLAY{6};
    constexpr pk::zindex_t CAMERA_ZINDEX_MAX{7};

    constexpr float CAMERA_ZOOM_MIN{0.25f};
    constexpr float CAMERA_ZOOM_MAX{2.5f};
    


}