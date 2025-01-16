#pragma once
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <vector>
#include <memory>
#include <cassert>
#include <typeinfo>
#include "System.hpp"
#include "components.hpp"
#include "../constants.hpp"
#include "../util/types.hpp"


namespace pk {


    class SystemManager {

    private:        
        std::map<pk::component_t, std::unique_ptr<pk::System>> system_map{};
        std::vector<pk::component_t> draw_order{};
        std::vector<pk::component_t> update_order;

    public:
        template<typename T, class SystemClass>
        void register_system() {
            const pk::component_t component_id = pk::get_component_id<T>();
            assert(this->system_map.find(component_id) == this->system_map.end());
            this->system_map.emplace(component_id, std::make_unique<SystemClass>());
        }

    public:
        SystemManager() {
            this->update_order.push_back(pk::get_component_id<pk::SpriteAnimation>());
            this->update_order.push_back(pk::get_component_id<pk::Player>());
            assert(this->update_order.size() == pk::NUM_UPDATABLE_COMPONENTS);

            this->draw_order.push_back(pk::get_component_id<pk::Sprite>());
            this->draw_order.push_back(pk::get_component_id<pk::SpriteAnimation>());
            assert(this->draw_order.size() == pk::NUM_DRAWABLE_COMPONENTS);

        }

        template<typename T>
        void insert(const pk::entity_t e) {            
            this->system_map[pk::get_component_id<T>()]->entities.insert(e);
        }

        template<typename T>
        void erase(const pk::entity_t e) {            
            this->system_map[pk::get_component_id<T>()]->entities.erase(e);            
        }

        void update(const float dt) {
            for (const pk::component_t component_id : this->update_order) {
                this->system_map[component_id]->update(dt);
            }
        }

        void draw() {
            for (const pk::component_t component_id : this->draw_order) {
                this->system_map[component_id]->draw();
            }
        }

        void entity_destroy(const pk::entity_t e) {
            for (auto& p : this->system_map) {
                p.second->entities.erase(e);
            }            
        }

        void clear() {
            for (auto& p : this->system_map) {
                p.second->entities.clear();
            }            
        }

        template<typename T>
        const std::set<pk::entity_t>& get_entities_by_system() const {
            return this->system_map.at(pk::get_component_id<T>())->entities;
        }
        
        std::size_t num_registered_systems() const {
            return this->system_map.size();
        }
        
    };
    
} // namespace pk
