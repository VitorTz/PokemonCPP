#pragma once
#include <cassert>
#include <memory>
#include <typeinfo>
#include "ComponentArray.hpp"
#include "../util/types.hpp"


namespace pk {

    class ComponentManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::IComponentArray>> component_array_map{};
    
    private:
        template<typename T>
        pk::ComponentArray<T>* get_component_array() {
            return dynamic_cast<pk::ComponentArray<T>*>(
                this->component_array_map[typeid(T).hash_code()].get()
            )
        }

    public:        
        template<typename T>
        void register_component() {
            const std::size_t h = typeid(T).hash_code();
            assert(this->component_array_map.find(h) != this->component_array_map.end());
            this->component_array_map.emplace(h, std::make_unique<pk::ComponentArray<T>>());
        }   

        template<typename T>
        T& at(const pk::entity_t e) {
            return this->get_component_array<T>()->at(e);
        }

        template<typename T>
        void insert(const pk::entity_t e, T component) {
            this->get_component_array<T>()->insert(e, component);
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            this->component_array_map[typeid(T).hash_code()]->erase(e);
        }
        
        void entity_destroy(pk::entity_t e) {
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

    };
    
} // namespace pk
