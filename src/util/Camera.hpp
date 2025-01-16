#pragma once
#include <raylib.h>
#include <limits>
#include "../constants.hpp"


namespace pk {    

    class Camera {
        
    private:        
        Camera2D camera2D{
            pk::SCREEN_CENTER,
            pk::SCREEN_CENTER,
            0.0f,
            1.0f
        };        
        float max_x_pos{std::numeric_limits<float>::max()};
        float max_y_pos{std::numeric_limits<float>::max()};

    public:
        void set_max_x_pos(float x);
        void set_max_y_pos(float y);
        
        void add_zoom(float zoom);
        void set_zoom(float zoom);

        void set_target(float x, float y);
        void move(float delta_x, float delta_y);

        void begin_drawing() const;
        void end_drawing() const;

        void handle_user_input(float dt);

        void reset();
        
    };
    
} // namespace pk
