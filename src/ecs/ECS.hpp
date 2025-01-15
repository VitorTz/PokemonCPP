#pragma once
#include <memory>
#include <algorithm>
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "SystemManager.hpp"
#include "components.hpp"
#include "../util/Camera.hpp"


namespace pk {

    class ECS {

    private:
        std::unique_ptr<pk::EntityManager> entity{};
        std::unique_ptr<pk::ComponentManager> component{};
        std::unique_ptr<pk::SystemManager> system{};
        std::unique_ptr<pk::Camera> camera{};
        std::queue<pk::entity_t> entities_to_destroy{};
        bool should_destroy_all_entities{};

    public:
        ECS() : entity(std::make_unique<pk::EntityManager>()),
                component(std::make_unique<pk::ComponentManager>()),
                system(std::make_unique<pk::SystemManager>()) { 
            // Component
            this->component->register_component<pk::Transform>();
            this->component->register_component<pk::Sprite>();
            this->component->register_component<pk::SpriteAnimation>();
            // Check
            assert(this->component->num_registered_components() == pk::NUM_COMPONENTS);
            
            // System
            // All Components
            this->system->register_system<pk::Transform, pk::TransformSystem>();
            this->system->register_system<pk::Sprite, pk::SpriteSystem>();
            this->system->register_system<pk::SpriteAnimation, pk::SpriteAnimationSystem>();            
            // Check
            assert(this->system->num_registered_systems() == pk::NUM_COMPONENTS);
        }
            
        
        pk::entity_t entity_create(
            const pk::zindex_t zindex, 
            const float pos_x,
            const float pos_y,
            const bool add_to_camera
        ) {
            const pk::entity_t e = this->entity->entity_create();
            this->add_component<pk::Transform>(e, pk::Transform{pos_x, pos_y, zindex});            
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

        void entity_destroy(const pk::entity_t e) {
            this->entities_to_destroy.push(e);
        }

        void destroy_all_entities() {
            this->should_destroy_all_entities = true;
        }

        template<typename T>
        T& add_component(const pk::entity_t e, T component) {
            this->system->insert<T>(e);            
            return this->component->insert<T>(e, std::move(component));
        }

        template<typename T>
        void rmv_component(const pk::entity_t e) {
            this->component->erase<T>(e);
            this->system->erase<T>(e);
        }

        template<typename T>
        T& get_component(const pk::entity_t e) {
            return this->component->at<T>(e);
        }

        pk::Transform& get_transform(const pk::entity_t e) {            
            return this->component->at<pk::Transform>(e);
        }

        void update(const float dt) {
            this->system->update(dt);

            if (this->should_destroy_all_entities) {
                this->should_destroy_all_entities = false;
                this->entity->clear();
                this->component->clear();
                this->system->clear();                
                this->entities_to_destroy = std::queue<pk::entity_t>();
            }

            while (this->entities_to_destroy.empty()) {
                const pk::entity_t e = this->entities_to_destroy.front();
                this->entities_to_destroy.pop();                
                this->entity->entity_destroy(e);
                this->component->entity_destroy(e);
                this->system->entity_destroy(e);
            }
        }

        void draw() {
            this->camera->begin_drawing();
            this->system->draw();
            this->camera->end_drawing();
        }

        void reset() {
            this->should_destroy_all_entities = false;
            this->entity->clear();
            this->component->clear();
            this->system->clear();            
            this->entities_to_destroy = std::queue<pk::entity_t>();
        }

        pk::Camera* get_camera() {
            return this->camera.get();
        }

        const pk::EntityManager* get_entity_manager() const {
            return this->entity.get();
        }

        const pk::ComponentManager* get_component_manager() const {
            return this->component.get();
        }

        const pk::SystemManager* get_system_manager() const {
            return this->system.get();
        }
    
    };
    
} // namespace pk
