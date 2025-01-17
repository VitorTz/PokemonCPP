#pragma once
#include <cassert>
#include <memory>
#include "components.hpp"
#include "ComponentArray.hpp"
#include "../../util/types.hpp"


namespace pk {

    class ComponentManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::IComponentArray>> component_array_map{};
    
    private:
        template<typename T>
        pk::ComponentArray<T>* get_component_array() {
            return dynamic_cast<pk::ComponentArray<T>*>(
                this->component_array_map[pk::get_component_id<T>()].get()
            );
        }

        template<typename T>
        void register_component() {
            const pk::component_t component_id = pk::get_component_id<T>();
            assert(this->component_array_map.find(component_id) == this->component_array_map.end());
            this->component_array_map.emplace(component_id, std::make_unique<pk::ComponentArray<T>>());
        }

    public:
        ComponentManager() {
            this->register_component<pk::Transform>();
            this->register_component<pk::Sprite>();
            this->register_component<pk::SpriteAnimation>();
            this->register_component<pk::Player>();
            this->register_component<pk::Water>();
            this->register_component<pk::Transition>();
            assert(this->component_array_map.size() == pk::NUM_COMPONENTS);
        }

        template<typename T>
        T& at(const pk::entity_t e) {
            return this->get_component_array<T>()->at(e);
        }

        template<typename T>
        T& insert(const pk::entity_t e, T component) {
            this->get_component_array<T>()->insert(e, component);
            return this->at<T>(e);
        }

        template<typename T>
        void erase(const pk::entity_t e) {            
            this->component_array_map[pk::get_component_id<T>()]->erase(e);
        }
        
        void entity_destroy(const pk::entity_t e) {
            for (auto& pair : this->component_array_map) {
                pair.second->erase(e);
            }
        }

        void clear() {
            for (auto& pair : this->component_array_map) {
                pair.second->clear();
            }
        }

        std::size_t num_registered_components() const {
            return this->component_array_map.size();
        }

        std::size_t count_num_active_components() const {
            std::size_t n{};
            for (auto& pair : this->component_array_map) {
                n += pair.second->size();
            }
            return n;
        }

    };
    
} // namespace pk
