#pragma once
#include <raylib.h>


namespace pk {


    class WaterShader {

    private:
        Shader shader;

    private:
        float seconds{};
        int secondsLoc;
        int freqXLoc;
        int freqYLoc;
        int ampXLoc;
        int ampYLoc;
        int speedXLoc;
        int speedYLoc;

    public:
        float freqX;
        float freqY;
        float ampX;
        float ampY;
        float speedX;
        float speedY;

    public:
        WaterShader();
        void update_seconds(float dt);
        void begin_shader_mode() const;
        void end_shader_mode() const;

    };

}