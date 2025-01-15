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
    class ComponentArray : public pk::IComponentArray {

    private:
        std::array<T, pk::MAX_ENTITIES> arr{};
        std::unordered_map<pk::entity_t, std::size_t> entity_to_index{};
        std::unordered_map<std::size_t, pk::entity_t> index_to_entity{};
        std::size_t mSize{};

    public:
        ComponentArray();
        T& at(pk::entity_t e);
        void insert(pk::entity_t e, T component);
        void erase(pk::entity_t e) override;
        void clear() override;
        std::size_t size() const override;

    };
    
} // namespace pk
