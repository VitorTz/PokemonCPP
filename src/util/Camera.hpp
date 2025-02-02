#pragma once
#include <raylib.h>
#include <limits>
#include <map>
#include <array>
#include <vector>
#include "types.hpp"
#include "../ecs/system/SystemManager.hpp"
#include "../constants.hpp"


namespace pk {    

    class Camera {
        
    private:
        std::map<pk::zindex_t, std::vector<std::pair<float, pk::entity_t>>> entities{};
        std::array<bool, pk::MAX_ENTITIES> is_on_camera{};
        Camera2D camera2D{
            pk::SCREEN_CENTER,
            pk::SCREEN_CENTER,
            0.0f,
            1.0f
        };        
        float max_x_pos{std::numeric_limits<float>::max()};
        float max_y_pos{std::numeric_limits<float>::max()};
        std::size_t mSize{};

    public:
        Camera();
        void insert(pk::entity_t, pk::zindex_t zindex);
        void erase(pk::entity_t, pk::zindex_t zindex);
        void draw(pk::SystemManager* system_manager);

        void set_max_x_pos(float x);
        void set_max_y_pos(float y);
        
        void add_zoom(float zoom);
        void set_zoom(float zoom);
        float get_zoom() const;

        void set_target(float x, float y);
        float get_target_x() const;
        float get_target_y() const;

        void move(float delta_x, float delta_y);

        void begin_drawing() const;
        void end_drawing() const;

        void handle_user_input(float dt);

        void clear();
        void reset();

        const Camera2D& get_camera2D() const {
            return this->camera2D;
        }

        std::size_t num_entities();

    };
    
} // namespace pk
