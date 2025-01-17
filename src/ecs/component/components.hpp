#pragma once
#include <raylib.h>
#include <typeinfo>
#include "../../scene/SceneID.hpp"
#include "../../util/TexturePool.hpp"
#include "../../util/types.hpp"


namespace pk {

    constexpr std::size_t NUM_COMPONENTS{6};
    constexpr std::size_t NUM_DRAWABLE_COMPONENTS{4};
    constexpr std::size_t NUM_UPDATABLE_COMPONENTS{3};

    template<typename T>
    pk::component_t get_component_id() {
        return typeid(T).hash_code();
    }

    typedef struct transform {
        Vector2 pos{};
        Vector2 size{};
        pk::zindex_t zindex{};
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
        Texture2D texture{};
        Rectangle texture_rect{};
        std::uint8_t current_frame{};
        std::uint8_t max_frame{};
        std::uint8_t current_sprite{};
        std::uint8_t max_sprite{};
        std::uint8_t cols{};
        sprite_animation() = default;
        explicit sprite_animation(
            const SpriteAnimationSource& source
        ) : texture(pk::gTexturePool.get(source.sprite_sheet.image_path)),
            texture_rect({0.0f, 0.0f, source.sprite_sheet.sprite_width, source.sprite_sheet.sprite_height}),
            max_frame(source.speed),
            max_sprite(source.sprite_sheet.rows * source.sprite_sheet.cols),
            cols(source.sprite_sheet.cols) { }
    } SpriteAnimation;

    typedef struct player {
        char direction[2]{'i', 'd'};
        char last_direction[2]{'i', 'd'};
    } Player;

    typedef struct water {
        Texture2D texture{};
        water() = default;
        explicit water(const Texture2D &texture) : texture(texture) { }
    } Water;

    typedef struct transition {
        bool is_hovered{};
        pk::SceneID scene_id{};
        transition() = default;
        explicit transition(const pk::SceneID scene_id) : scene_id(scene_id) { }
    } Transition;
    
} // namespace pk
