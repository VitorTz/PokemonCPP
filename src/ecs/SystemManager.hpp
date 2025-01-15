#pragma once
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <memory>
#include <cassert>
#include <typeinfo>
#include "../constants.hpp"
#include "../util/types.hpp"


namespace pk {

    class System {

    public:
        std::unordered_set<pk::entity_t> entities{};

    public:
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void draw(pk::entity_t e) = 0;

    };

    class TransformSystem : public System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SpriteSystem : public System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SpriteAnimationSystem : public System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class SystemManager {

    private:
        std::unordered_map<pk::component_t, std::unique_ptr<pk::System>> system_map{};        
        std::unordered_set<pk::component_t> drawable_components{};
        std::map<pk::entity_t, std::unordered_set<pk::component_t>> entity_to_drawable_components{};
        std::vector<pk::component_t> update_order{};

    public:
        template<typename T, class SystemClass>
        void register_system() {
            const std::size_t h = typeid(T).hash_code();
            assert(this->system_map.find(h) == this->system_map.end());
            this->system_map.emplace(h, std::make_unique<SystemClass>());
        }

        template<typename T>
        void register_drawable_component() {            
            this->drawable_components.insert(typeid(T).hash_code());
        }

        template<typename T>
        void register_updatable_component() {
            this->update_order.push_back(typeid(T).hash_code());
        }

    public:
        template<typename T>
        void insert(const pk::entity_t e) {
            const std::size_t h = typeid(T).hash_code();
            this->system_map[h]->entities.insert(e);
            if (this->drawable_components.find(h) != this->drawable_components.end()) {
                this->entity_to_drawable_components.insert({e, h});
            }
        }

        template<typename T>
        void erase(const pk::entity_t e) {
            const std::size_t h = typeid(T).hash_code();
            this->system_map[h]->entities.erase(e);
            this->entity_to_drawable_components.erase(e);
        }

        void update(const float dt) {
            for (const pk::component_t component : this->update_order) {
                this->system_map[component]->update(dt);
            }
        }

        void draw(const std::vector<std::pair<float, pk::entity_t>>& entities) {
            for (const auto& pair : entities) {
                for (const pk::component_t component : this->entity_to_drawable_components[pair.second]) {
                    this->system_map[component]->draw(pair.second);
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
        
        std::size_t num_registered_systems() const {
            return this->system_map.size();
        }

        std::size_t num_registered_drawable_components() const {
            return this->drawable_components.size();
        }

        std::size_t num_registered_updatable_components() const {
            return this->drawable_components.size();
        }
        
    };
    
} // namespace pk
