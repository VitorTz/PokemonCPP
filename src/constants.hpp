#pragma once
#include "util/types.hpp"
#include "scene/SceneID.hpp"


namespace pk {
    
    constexpr int SCREEN_WIDTH{1280};
    constexpr int SCREEN_HEIGHT{720};
    constexpr char WINDOW_TITLE[]{"Pokemon"};
    constexpr int FPS{60};

    constexpr pk::SceneID MAIN_SCENE{pk::TitleScreenID};
    constexpr pk::entity_t MAX_ENTITIES{4096};

}