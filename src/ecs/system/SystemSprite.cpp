#include "System.hpp"
#include "../EcsManager.hpp"


void pk::SpriteSystem::draw(const pk::entity_t e) {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();
    const pk::Sprite& sprite = ecs->get_component<pk::Sprite>(e);
    const pk::Transform& transform = ecs->get_transform(e);
    DrawTextureV(sprite.texture, transform.pos, WHITE);
}
