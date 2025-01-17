#pragma once
#include <cstdint>


namespace pk {

    typedef std::uint32_t entity_t;
    typedef std::size_t component_t;
    typedef std::int8_t zindex_t;

    typedef struct sprite_sheet {
        const char* image_path{};
        float sprite_width{};
        float sprite_height{};
        std::uint8_t rows{};
        std::uint8_t cols{};
    } SpriteSheet;

    typedef struct sprite_animation_source {
        SpriteSheet sprite_sheet{};
        std::uint8_t speed{};
    } SpriteAnimationSource;

    enum GameObjGroup {
        CharacterGroup,
        CoastGroup,
        MonsterGroup,
        SpriteGroup,
        TransitionGroup,
        CollisionGroup,
        WaterGroup
    };

    enum CharacterID {
        PlayerID,
        NurseID
    };
    
} // namespace pk
