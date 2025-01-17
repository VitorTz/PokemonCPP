#include "System.hpp"
#include "../EcsManager.hpp"


void pk::PlayerSystem::update(const float dt) {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();
    Rectangle collision_rect = pk::PLAYER_COLLISION_RECT;

    for (const pk::entity_t e : this->entities) {
        pk::Player& player = ecs->get_component<pk::Player>(e);
        pk::SpriteAnimation& sprite_animation = ecs->get_component<pk::SpriteAnimation>(e);
        pk::Transform& transform = ecs->get_transform(e);

        // Movement
            Vector2 direction{0.0f, 0.0f};
            player.last_direction[0] = player.direction[0];
            player.last_direction[1] = player.direction[1];
            player.direction[0] = 'i';

            if (IsKeyDown(pk::KEY_MOVE_UP)) {
                direction.y = -1.0f;
                player.direction[1] = 'u';
                player.direction[0] = 'm';
            } else if (IsKeyDown(pk::KEY_MOVE_DOWN)) {
                direction.y = 1.0f;
                player.direction[1] = 'd';
                player.direction[0] = 'm';
            }

            if (IsKeyDown(pk::KEY_MOVE_LEFT)) {
                direction.x = -1.0f;
                player.direction[1] = 'l';
                player.direction[0] = 'm';
            } else if (IsKeyDown(pk::KEY_MOVE_RIGHT)) {
                direction.x = 1.0f;
                player.direction[1] = 'r';
                player.direction[0] = 'm';
            }

            direction = Vector2Normalize(direction);

            // horizontal movement
            transform.pos.x += dt * pk::PLAYER_SPEED * direction.x;
            collision_rect.x = transform.pos.x + transform.size.x / 2.0f - pk::PLAYER_COLLISION_RECT.width / 2.0f;
            collision_rect.y = transform.pos.y + transform.size.y - pk::PLAYER_COLLISION_RECT.height;
            if (ecs->check_static_collision(collision_rect)) {
                transform.pos.x -= dt * pk::PLAYER_SPEED * direction.x;
            }

            // vertical movement
            transform.pos.y += dt * pk::PLAYER_SPEED * direction.y;
            collision_rect.x = transform.pos.x + transform.size.x / 2.0f - pk::PLAYER_COLLISION_RECT.width / 2.0f;
            collision_rect.y = transform.pos.y + transform.size.y - pk::PLAYER_COLLISION_RECT.height;
            if (ecs->check_static_collision(collision_rect)) {
                transform.pos.y -= dt * pk::PLAYER_SPEED * direction.y;
            }

            ecs->get_camera()->set_target(
                transform.pos.x + transform.size.x / 2.0f,
                transform.pos.y + transform.size.y / 2.0f
            );

        // Sprite Animation
        switch (player.direction[1]) {
            case 'd':
                sprite_animation.texture_rect.y = 0.0f;
                break;
            case 'l':
                sprite_animation.texture_rect.y = pk::CHARACTER_SIZE;
                break;
            case 'r':
                sprite_animation.texture_rect.y = pk::CHARACTER_SIZE * 2.0f;
                break;
            case 'u':
                sprite_animation.texture_rect.y = pk::CHARACTER_SIZE * 3.0f;
                break;
            default:
                break;
        }

        if (player.direction[0] == 'i') {
            sprite_animation.texture_rect.x = 0.0f;
        }

    }
}