#pragma once
#include <array>
#include <unordered_map>
#include "../constants.hpp"
#include "../util/types.hpp"


namespace pk {
    
    class IComponentArray {    

    public:
        virtual ~IComponentArray() = default;
        virtual void erase(pk::entity_t e) = 0;
        virtual void clear() = 0;
        virtual std::size_t size() const = 0;

    };

    template<typename T>
    class ComponentArray final : public pk::IComponentArray {

    private:
        std::array<T, pk::MAX_ENTITIES> arr{};
        std::unordered_map<pk::entity_t, std::size_t> entity_to_index{};
        std::unordered_map<std::size_t, pk::entity_t> index_to_entity{};
        std::size_t mSize{};

    public:
        ComponentArray() {
            this->entity_to_index.reserve(pk::MAX_ENTITIES);
            this->index_to_entity.reserve(pk::MAX_ENTITIES);
        }
        
        T& at(const pk::entity_t e) {
            return this->arr[this->entity_to_index.at(e)];
        }

        T& insert(const pk::entity_t e, const T component) {
            assert(this->entity_to_index.find(e) == this->entity_to_index.end());
            this->entity_to_index[e] = this->mSize;
            this->index_to_entity[this->mSize] = e;
            this->arr[this->mSize++] = component;  
            return this->arr[this->mSize - 1];
        }

        void erase(const pk::entity_t e) override {
            if (this->entity_to_index.find(e) == this->entity_to_index.end()) {
                return;
            }

            const std::size_t last_component_index = --this->mSize;
            const std::size_t removed_component_index = this->entity_to_index[e];
            const pk::entity_t last_entity = this->index_to_entity[last_component_index];

            this->entity_to_index[last_entity] = removed_component_index;
            this->index_to_entity[removed_component_index] = last_entity;

            this->entity_to_index.erase(e);
            this->index_to_entity.erase(last_component_index);

            std::swap(this->arr[removed_component_index], this->arr[last_component_index]);
        }
        
        void clear() override {
            this->entity_to_index.clear();
            this->index_to_entity.clear();
            this->mSize = 0;
        }

        std::size_t size() const override {
            return this->mSize;
        }

    };
    
} // namespace pk
