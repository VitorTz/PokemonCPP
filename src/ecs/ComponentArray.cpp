#include "ComponentArray.hpp"
#include <cassert>


template<typename T>
pk::ComponentArray<T>::ComponentArray() {
    this->entity_to_index.reserve(pk::MAX_ENTITIES);
    this->index_to_entity.reserve(pk::MAX_ENTITIES);
}


template<typename T>
void pk::ComponentArray<T>::insert(const pk::entity_t e, T component) {
    assert(this->entity_to_index.find(e) == this->entity_to_index.end());
    this->entity_to_index[e] = this->mSize;
    this->index_to_entity[this->mSize] = e;
    this->arr[this->mSize++] = component;    
}


template<typename T>
T& pk::ComponentArray<T>::at(const pk::entity_t e) {    
    return this->arr[this->entity_to_index.at(e)];
}


template<typename T>
void pk::ComponentArray<T>::erase(const pk::entity_t e) {
    if (this->entity_to_index.find(e) != this->entity_to_index.end()) {
        return;
    }

    const std::size_t last_component_index = --this->mSize;
    const std::size_t removed_component_index = this->entity_to_index[e];
    const pk::entity_t last_entity = this->index_to_entity[last_component_index];

    this->entity_to_index[last_entity] = removed_component_index;
    this->index_to_entity[removed_component_index] = last_entity;

    this->entity_to_index.erase(e);
    this->index_to_entity.erase(last_component_index);

    std::swap(
        this->arr.begin() + removed_component_index,
        this->arr.begin() + last_component_index
    )
}


template<typename T>
void pk::ComponentArray<T>::clear() {
    this->entity_to_index.clear();
    this->index_to_entity.clear();
    this->mSize = 0;
}


template<typename T>
std::size_t pk::ComponentArray<T>::size() const {    
    return this->mSize;
}