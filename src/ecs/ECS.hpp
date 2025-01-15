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
            assert(this->component->num_registered_components() == pk::NUM_COMPONENTS);
            
            // System
            // All Components
            this->system->register_system<pk::Transform, pk::TransformSystem>();
            this->system->register_system<pk::Sprite, pk::SpriteSystem>();
            this->system->register_system<pk::SpriteAnimation, pk::SpriteAnimationSystem>();
            // Drawable Components
            this->system->register_drawable_component<pk::Sprite>();
            this->system->register_drawable_component<pk::SpriteAnimation>();
            // Updatable Componens
            this->system->register_updatable_component<pk::SpriteAnimation>();
            // Check
            assert(this->system->num_registered_systems() == pk::NUM_COMPONENTS);
            assert(this->system->num_registered_drawable_components() == pk::NUM_DRAWABLE_COMPONENTS);
            assert(this->system->num_registered_updatable_components() == pk::NUM_UPDATABLE_COMPONENTS);
        }
            
        
        pk::entity_t entity_create(pk::zindex_t zindex, bool add_to_camera) {
            const pk::entity_t e = this->entity->entity_create();
            this->add_component<pk::Transform>(e, pk::Transform{zindex});
            if (add_to_camera) {
                this->camera->insert(e, zindex);
            }
            return e;
        }

        void entity_destroy(const pk::entity_t e) {
            this->entities_to_destroy.push(e);
        }

        void destroy_all_entities() {
            this->should_destroy_all_entities = true;
        }

        template<typename T>
        void add_component(const pk::entity_t e, T component) {
            this->component->insert<T>(e, std::move(component));
            this->system->insert<T>(e);
        }

        void update(const float dt) {
            this->system->update(dt);

            if (this->should_destroy_all_entities) {
                this->should_destroy_all_entities = false;
                this->entity->clear();
                this->component->clear();
                this->system->clear();
                this->camera->clear();
                this->entities_to_destroy = std::queue<pk::entity_t>();
            }

            while (this->entities_to_destroy.empty()) {
                const pk::entity_t e = this->entities_to_destroy.front();
                this->entities_to_destroy.pop();
                this->camera->erase(e, this->component->at<pk::Transform>(e).zindex);
                this->entity->entity_destroy(e);
                this->component->entity_destroy(e);
                this->system->entity_destroy(e);
            }
        }

        void draw() {
            pk::CameraEntitiesMap* entities_map = this->camera->get_entities_map();
            for (auto& pair : *entities_map) {
                for (std::pair<float, pk::entity_t>& pair1 : pair.second) {
                    pk::Transform& transform = this->component->at<pk::Transform>(pair1.second);
                    pair1.first = transform.pos.y + transform.size.y / 2.0f;
                    std::sort(pair.second.begin(), pair.second.end());
                    this->system->draw(pair.second);
                }
                
            }
        }
    
    };
    
} // namespace pk
