#pragma once
#include <map>
#include <raylib.h>
#include <vector>
#include <array>
#include "types.hpp"
#include "../constants.hpp"


namespace pk {

    typedef std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> CameraEntitiesMap;

    class Camera {
        
    private:
        pk::CameraEntitiesMap zindex_to_entities{};
        std::array<bool, pk::MAX_ENTITIES> is_on_camera{};
        Camera2D camera2D{};
        std::size_t mSize{};

    public:
        Camera();
        void insert(pk::entity_t e, pk::zindex_t zindex);
        void erase(pk::entity_t e, pk::zindex_t zindex);        
        pk::CameraEntitiesMap* get_entities_map();
        void clear();        
        std::size_t size() const;
    
    };
    
} // namespace pk
