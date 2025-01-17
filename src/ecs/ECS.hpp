#pragma once
#include <algorithm>
#include "entity/EntityManager.hpp"
#include "component/components.hpp"
#include "component/ComponentManager.hpp"
#include "system/SystemManager.hpp"
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
            // Collisions
            this->static_collisions.reserve(1024);
        }
        
        pk::entity_t entity_create(
            const pk::zindex_t zindex, 
            const float pos_x,
            const float pos_y,
            const bool should_add_to_camera
        ) {
            assert(zindex >= pk::CAMERA_ZINDEX_MIN && zindex < pk::CAMERA_ZINDEX_MAX);
            const pk::entity_t e = this->entity.entity_create();
            this->add_component<pk::Transform>(e, pk::Transform{pos_x, pos_y, zindex});
            if (should_add_to_camera) {
                this->camera.insert(e, zindex);
            }
            return e;
        }

         pk::entity_t sprite_create(
            const pk::zindex_t zindex,
            const char* filepath,
            const float pos_x,
            const float pos_y
        ) {
            const pk::entity_t e = this->entity_create(zindex, pos_x, pos_y, true);
            const pk::Sprite& sprite = this->add_component<pk::Sprite>(e, pk::Sprite{filepath});
            this->get_transform(e).size = {
                static_cast<float>(sprite.texture.width),
                static_cast<float>(sprite.texture.height)
            };
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
                this->camera.clear();
                this->entities_to_destroy = std::queue<pk::entity_t>();
            }

            while (this->entities_to_destroy.empty() == false) {
                const pk::entity_t e = this->entities_to_destroy.front();
                this->camera.erase(e, this->get_transform(e).zindex);
                this->entities_to_destroy.pop();
                this->entity.entity_destroy(e);
                this->component.entity_destroy(e);
                this->system.entity_destroy(e);
            }
            
            this->system.update(dt);
            this->camera.handle_user_input(dt);
        }

        void draw() {
            this->camera.draw(&this->system);
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
            this->camera.clear();
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
                for (const Rectangle& rect : this->static_collisions) {
                    DrawRectangleLinesEx(rect, 2.0f, RED);
                }
                for (const pk::entity_t e : this->system.get_entities_by_system<pk::Transition>()) {
                    const pk::Transition& transition = this->get_component<pk::Transition>(e);
                    const pk::Transform& transform = this->get_transform(e);
                    DrawRectangleLinesEx(
                        Rectangle{transform.pos.x, transform.pos.y, transform.size.x, transform.size.y},
                        2.0,
                        BLACK
                    );
                    DrawText(
                        pk::SCENE_NAMES[transition.scene_id],
                        transform.pos.x,
                        transform.pos.y,
                        18,
                        WHITE
                    );
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
