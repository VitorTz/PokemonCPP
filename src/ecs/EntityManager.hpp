#pragma once
#include <queue>
#include "../constants.hpp"


namespace pk {

    class EntityManager {

    private:
        std::queue<pk::entity_t> q{};
        std::size_t mSize{};
    
    public:
        EntityManager();
        pk::entity_t entity_create();
        void entity_destroy(pk::entity_t e);
        void clear();
        std::size_t size() const;

    };

    
} // namespace pk
