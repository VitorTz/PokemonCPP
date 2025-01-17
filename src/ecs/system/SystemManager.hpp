#pragma once
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <cassert>
#include "System.hpp"
#include "../component/components.hpp"
#include "../../util/types.hpp"
#include "../../constants.hpp"


namespace pk {


    class SystemManager {

    private:        
        std::map<pk::component_t, std::unique_ptr<pk::System>> system_map{};
        std::unordered_map<pk::entity_t, std::set<pk::component_t>> entity_to_drawable_components{};
        std::unordered_set<pk::component_t> drawable_components{};
        std::vector<pk::component_t> draw_order{};
        std::vector<pk::component_t> update_order{};

    private:
        template<typename T, class SystemClass>
        void register_system() {
            const pk::component_t component_id = pk::get_component_id<T>();
            assert(this->system_map.find(component_id) == this->system_map.end());
            this->system_map.emplace(component_id, std::make_unique<SystemClass>());
        }

        template<typename T>
        void register_drawable_component() {
            this->drawable_components.insert(pk::get_component_id<T>());
        }

    public:
        SystemManager() {
            for (pk::entity_t e = 0; e < pk::MAX_ENTITIES; e++) {
                this->entity_to_drawable_components.insert({e, {}});
            }

            // Register Systems
            this->register_system<pk::Transform, pk::TransformSystem>();
            this->register_system<pk::Sprite, pk::SpriteSystem>();
            this->register_system<pk::SpriteAnimation, pk::SpriteAnimationSystem>();
            this->register_system<pk::Player, pk::PlayerSystem>();
            this->register_system<pk::Water, pk::WaterSystem>();
            this->register_system<pk::Transition, pk::TransitionSystem>();
            assert(this->system_map.size() == pk::NUM_COMPONENTS);

            // Update order
            this->update_order.push_back(pk::get_component_id<pk::SpriteAnimation>());
            this->update_order.push_back(pk::get_component_id<pk::Player>());
            this->update_order.push_back(pk::get_component_id<pk::Water>());
            assert(this->update_order.size() == pk::NUM_UPDATABLE_COMPONENTS);

            // Register Drawable components
            this->register_drawable_component<pk::SpriteAnimation>();
            this->register_drawable_component<pk::Sprite>();
            this->register_drawable_component<pk::Water>();
            this->register_drawable_component<pk::Transition>();
            assert(this->drawable_components.size() == pk::NUM_DRAWABLE_COMPONENTS);

            // Draw order
            this->draw_order.push_back(pk::get_component_id<pk::Sprite>());
            this->draw_order.push_back(pk::get_component_id<pk::SpriteAnimation>());
            this->draw_order.push_back(pk::get_component_id<pk::Water>());
            this->draw_order.push_back(pk::get_component_id<pk::Transition>());
            assert(this->draw_order.size() == pk::NUM_DRAWABLE_COMPONENTS);
        }

        template<typename T>
        void insert(const pk::entity_t e) {
            const pk::component_t component_id = pk::get_component_id<T>();
            this->system_map[component_id]->entities.insert(e);
            if (this->drawable_components.find(component_id) != this->drawable_components.end()) {
                this->entity_to_drawable_components[e].insert(component_id);
            }
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            const pk::component_t component_id = pk::get_component_id<T>();
            this->system_map[component_id]->entities.erase(e);
            this->entity_to_drawable_components[e].erase(component_id);
        }

        void update(const float dt) {
            for (const pk::component_t component_id : this->update_order) {
                this->system_map[component_id]->update(dt);
            }
        }

        void draw(const std::vector<std::pair<float, pk::entity_t>>& entities) {
            for (const auto& p : entities) {
                for (const pk::component_t component_id : this->entity_to_drawable_components[p.second]) {
                    this->system_map[component_id]->draw(p.second);
                }
            }
        }

        void entity_destroy(const pk::entity_t e) {
            for (auto& p : this->system_map) {
                p.second->entities.erase(e);
            }
            this->entity_to_drawable_components[e].clear();
        }

        void clear() {
            for (auto& p : this->system_map) {
                p.second->entities.clear();
            }
            for (auto& p : this->entity_to_drawable_components) {
                p.second.clear();
            }
        }

        template<typename T>
        const std::set<pk::entity_t>& get_entities_by_system() const {
            return this->system_map.at(pk::get_component_id<T>())->entities;
        }

    };
    
} // namespace pk
