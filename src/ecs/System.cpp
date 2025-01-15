#include "System.hpp"
#include "EcsManager.hpp"


static std::vector<std::pair<float, pk::entity_t>> entities_vec[pk::CAMERA_ZINDEX_MAX];


static void sort_entities(const std::set<pk::entity_t>& entity_set) {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();

    for (pk::zindex_t z = pk::CAMERA_ZINDEX_MIN; z < pk::CAMERA_ZINDEX_MAX; z++) {
        entities_vec[z].clear();
    }

    for (pk::entity_t e : entity_set) {
        const pk::Transform& transform = ecs->get_transform(e);
        entities_vec[transform.zindex].push_back(
            { transform.pos.y + transform.size.y / 2.0f, e }
        );
    }

    for (pk::zindex_t z = pk::CAMERA_ZINDEX_MIN; z < pk::CAMERA_ZINDEX_MAX; z++) {
        std::sort(entities_vec[z].begin(), entities_vec[z].end());
    }
}


/////////////////////////// TRANSFORM  /////////////////////////
void pk::TransformSystem::update([[maybe_unused]] const float dt) {

}


void pk::TransformSystem::draw() {

}


///////////////////////////  SPRITE  //////////////////////////
void pk::SpriteSystem::update([[maybe_unused]] const float dt) {

}


void pk::SpriteSystem::draw() {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();
    sort_entities(this->entities);
    for (pk::zindex_t z = pk::CAMERA_ZINDEX_MIN; z < pk::CAMERA_ZINDEX_MAX; z++) {
        for (const auto& pair : entities_vec[z]) {
            const pk::Sprite& sprite = ecs->get_component<pk::Sprite>(pair.second);
            const pk::Transform& transform = ecs->get_transform(pair.second);
            DrawTextureV(sprite.texture, transform.pos, WHITE);
        }
    }
}


/////////////////////// SPRITE ANIMATION ///////////////////////
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


void pk::SpriteAnimationSystem::draw() {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();
    sort_entities(this->entities);
    for (pk::zindex_t z = pk::CAMERA_ZINDEX_MIN; z < pk::CAMERA_ZINDEX_MAX; z++) {
        for (const auto& pair : entities_vec[z]) {
            const pk::SpriteAnimation& sprite_animation = ecs->get_component<pk::SpriteAnimation>(pair.second);
            const pk::Transform& transform = ecs->get_transform(pair.second);
            DrawTextureRec(sprite_animation.texture, sprite_animation.texture_rect, transform.pos, WHITE);
        }
    }
}