#pragma once
#include <algorithm>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "components.hpp"
#include "../util/Camera.hpp"


namespace pk {

    class ECS {

    private:
        pk::EntityManager entity{};
        pk::ComponentManager component{};
        pk::SystemManager system{};
        pk::Camera camera{};
        std::queue<pk::entity_t> entities_to_destroy{};
        std::vector<Rectangle> static_collisions{};
        bool should_destroy_all_entities{};

    public:
        ECS() {
            // Component
            this->component.register_component<pk::Transform>();
            this->component.register_component<pk::Sprite>();
            this->component.register_component<pk::SpriteAnimation>();
            this->component.register_component<pk::Player>();
            // Check
            assert(this->component.num_registered_components() == pk::NUM_COMPONENTS);
            
            // System
            // All Components
            this->system.register_system<pk::Transform, pk::TransformSystem>();
            this->system.register_system<pk::Sprite, pk::SpriteSystem>();
            this->system.register_system<pk::SpriteAnimation, pk::SpriteAnimationSystem>();
            this->system.register_system<pk::Player, pk::PlayerSystem>();
            // Check
            assert(this->system.num_registered_systems() == pk::NUM_COMPONENTS);

            // Collisions
            this->static_collisions.reserve(1024);
        }
        
        pk::entity_t entity_create(
            const pk::zindex_t zindex, 
            const float pos_x,
            const float pos_y
        ) {
            const pk::entity_t e = this->entity.entity_create();
            this->add_component<pk::Transform>(e, pk::Transform{pos_x, pos_y, zindex});
            return e;
        }

         pk::entity_t sprite_create(
            const pk::zindex_t zindex,
            const char* filepath,
            const float pos_x,
            const float pos_y
        ) {
            pk::entity_t e = this->entity_create(zindex, pos_x, pos_y);
            const pk::Sprite& sprite = this->add_component<pk::Sprite>(e, pk::Sprite{filepath});
            this->get_transform(e).size = {
                static_cast<float>(sprite.texture.width),
                static_cast<float>(sprite.texture.height)
            };
            return e;
        }

        pk::entity_t player_create(const float pos_x, const float pos_y) {
            const pk::entity_t e = this->entity_create(pk::CAMERA_ZINDEX_WORLD, pos_x, pos_y);
            this->add_sprite_animation_component(e, pk::PLAYER_SPRITE_ANIMATION);
            this->add_component<pk::Player>(e, pk::Player{});
            return e;
        }

        void add_sprite_animation_component(const pk::entity_t e, const pk::SpriteAnimationSource& source) {
            this->add_component(e, pk::SpriteAnimation{source});
            this->get_transform(e).size = {
                source.sprite_sheet.sprite_width,
                source.sprite_sheet.sprite_height
            };
        }

        void entity_destroy(const pk::entity_t e) {
            this->entities_to_destroy.push(e);
        }

        void destroy_all_entities() {
            this->should_destroy_all_entities = true;
        }

        template<typename T>
        T& add_component(const pk::entity_t e, T component) {
            this->system.insert<T>(e);
            return this->component.insert<T>(e, std::move(component));
        }

        template<typename T>
        void rmv_component(const pk::entity_t e) const {
            this->component.erase<T>(e);
            this->system.erase<T>(e);
        }

        template<typename T>
        T& get_component(const pk::entity_t e) {
            return this->component.at<T>(e);
        }

        pk::Transform& get_transform(const pk::entity_t e) {
            return this->component.at<pk::Transform>(e);
        }

        void update(const float dt) {            
            if (this->should_destroy_all_entities == true) {
                this->should_destroy_all_entities = false;
                this->entity.clear();
                this->component.clear();
                this->system.clear();
                this->entities_to_destroy = std::queue<pk::entity_t>();
            }

            while (this->entities_to_destroy.empty() == false) {
                const pk::entity_t e = this->entities_to_destroy.front();
                this->entities_to_destroy.pop();
                this->entity.entity_destroy(e);
                this->component.entity_destroy(e);
                this->system.entity_destroy(e);
            }
            
            this->system.update(dt);
            this->camera.handle_user_input(dt);
        }

        void draw() {
            this->camera.begin_drawing();
            this->system.draw();
            this->camera.end_drawing();
            if (pk::DEBUG_MODE) {
                this->draw_debug();
            }
        }

        void reset() {
            this->should_destroy_all_entities = false;
            this->entity.clear();
            this->component.clear();
            this->system.clear();
            this->entities_to_destroy = std::queue<pk::entity_t>();
            this->static_collisions.clear();            
        }

        void add_static_collision(
            const float x, 
            const float y,
            const float width,
            const float height
        ) {
            this->static_collisions.push_back(Rectangle{x, y, width, height});
        }

        bool check_static_collision(const Rectangle& rect) {
            for (const Rectangle& other_rect : this->static_collisions) {
                if (CheckCollisionRecs(rect, other_rect)) {
                    return true;
                }
            }
            return false;
        }

        pk::Camera* get_camera() {
            return &this->camera;
        }

        const pk::EntityManager* get_entity_manager() const {
            return &this->entity;
        }

        const pk::ComponentManager* get_component_manager() const {
            return &this->component;
        }

        const pk::SystemManager* get_system_manager() const {
            return &this->system;
        }

        bool is_empty() const {
            return this->entity.size() == 0;
        }

    private:

        void draw_debug() {
            this->camera.begin_drawing();
                for (const pk::entity_t e : this->system.get_entities_by_system<pk::Player>()) {
                    const pk::Transform& transform = this->get_transform(e);
                    Rectangle player_collision_rect = pk::PLAYER_COLLISION_RECT;
                    player_collision_rect.x = transform.pos.x + transform.size.x / 2.0f - pk::PLAYER_COLLISION_RECT.width / 2.0f;
                    player_collision_rect.y = transform.pos.y + transform.size.y - pk::PLAYER_COLLISION_RECT.height;
                    DrawRectangleLinesEx(player_collision_rect, 2.0f, BLUE);
                }
            this->camera.end_drawing();

            // Overlay
            DrawRectangle(
                16,
                16,
                300,
                300,
                Color{0, 0, 0, 180}
            );
            DrawText(
                TextFormat("Entities: %d", this->entity.size()),
                20,
                40,
                18,
                LIME
            );
            DrawText(
                TextFormat("Components: %d", this->component.count_num_active_components()),
                    20,
                    60,
                    18,
                    LIME
            );
            DrawText(
                TextFormat("Camera Target: (%.2f, %.2f)", this->camera.get_target_x(), this->camera.get_target_y()),
                    20,
                    80,
                    18,
                    LIME
            );
            DrawText(
                TextFormat("Camera Zoom: %.2f", this->camera.get_zoom()),
                    20,
                    100,
                    18,
                    LIME
            );
        }

    };
    
} // namespace pk
