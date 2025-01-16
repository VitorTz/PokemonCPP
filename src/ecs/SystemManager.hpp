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

    public:
        template<typename T, class SystemClass>
        void register_system() {
            const pk::component_t component_id = pk::get_component_id<T>();
            assert(this->system_map.find(component_id) == this->system_map.end());
            this->system_map.emplace(component_id, std::make_unique<SystemClass>());
        }

    public:
        template<typename T>
        void insert(const pk::entity_t e) {            
            this->system_map[pk::get_component_id<T>()]->entities.insert(e);
        }

        template<typename T>
        void erase(const pk::entity_t e) {            
            this->system_map[pk::get_component_id<T>()]->entities.erase(e);            
        }

        void update(const float dt) {
            for (auto& pair : this->system_map) {
                pair.second->update(dt);
            }            
        }

        void draw() {
            for (auto& pair : this->system_map) {
                pair.second->draw();    
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
