#pragma once
#include <raylib.h>
#include <typeinfo>
#include "../util/TexturePool.hpp"
#include "../util/types.hpp"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{3};
    constexpr std::size_t NUM_DRAWABLE_COMPONENTS{2};
    constexpr std::size_t NUM_UPDATABLE_COMPONENTS{1};

    template<typename T>
    pk::component_t get_component_id() {
        return typeid(T).hash_code();
    }

    typedef struct transform {
        Vector2 pos{};
        Vector2 size{};
        pk::zindex_t zindex;
        transform() = default;
        explicit transform(const pk::zindex_t zindex) : zindex(zindex) { }
        transform(
            const float pos_x,
            const float pos_y,
            const pk::zindex_t zindex
        ) : pos({pos_x, pos_y}),
            zindex(zindex) { }
    } Transform;

    typedef struct sprite {
        Texture2D texture{};
        sprite() = default;
        explicit sprite(const char* filepath) : texture(pk::gTexturePool.get(filepath)) { }
    } Sprite;

    typedef struct sprite_animation {
        sprite_animation() = default;
        Texture2D texture{};
        Rectangle texture_rect{};
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
