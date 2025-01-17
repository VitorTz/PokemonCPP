#include "System.hpp"
#include "../EcsManager.hpp"


void pk::SpriteAnimationSystem::update(const float dt) {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();
    for (const pk::entity_t e : this->entities) {
        pk::SpriteAnimation& sprite_animation = ecs->get_component<pk::SpriteAnimation>(e);
        sprite_animation.current_frame++;
        if (sprite_animation.current_frame > sprite_animation.max_frame) {
            sprite_animation.current_frame = 0;
            sprite_animation.current_sprite = (sprite_animation.current_sprite + 1) % sprite_animation.max_sprite;
            sprite_animation.texture_rect.x = (sprite_animation.current_sprite % sprite_animation.cols) * sprite_animation.texture_rect.width;
            sprite_animation.texture_rect.y = (sprite_animation.current_sprite / sprite_animation.cols) * sprite_animation.texture_rect.height;
        }
    }
}


void pk::SpriteAnimationSystem::draw(const pk::entity_t e) {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();
    const pk::SpriteAnimation& sprite_animation = ecs->get_component<pk::SpriteAnimation>(e);
    const pk::Transform& transform = ecs->get_transform(e);
    DrawTextureRec(sprite_animation.texture, sprite_animation.texture_rect, transform.pos, WHITE);
}