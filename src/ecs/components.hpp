#pragma once
#include <raylib.h>
#include "../util/TexturePool.hpp"
#include "../util/types.hpp"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{3};
    constexpr std::size_t NUM_DRAWABLE_COMPONENTS{2};
    constexpr std::size_t NUM_UPDATABLE_COMPONENTS{1};


    typedef struct transform {
        Vector2 pos{};
        Vector2 size{};
        pk::zindex_t zindex;
        explicit transform(const pk::zindex_t zindex) : zindex(zindex) { }
    } Transform;

    typedef struct sprite {
        Texture2D texture{};
        explicit sprite(const char* filepath) : texture(pk::gTexturePool.get(filepath)) { }
    } Sprite;

    typedef struct sprite_animation {
        Texture2D texture{};
        std::uint8_t current_frame{};
        std::uint8_t max_frame{};
        std::uint8_t current_sprite{};
        std::uint8_t max_sprite{};        
        std::uint8_t cols{};
        sprite_animation(
            const char* filepath,
            std::uint8_t rows,
            std::uint8_t cols,
            std::uint8_t speed
        ) : texture(pk::gTexturePool.get(filepath)),
            max_frame(speed),
            max_sprite(rows * cols),
            cols(cols) { }
    } SpriteAnimation;
    
} // namespace pk
