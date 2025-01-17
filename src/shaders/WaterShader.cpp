#include "WaterShader.hpp"
#include "ShaderPool.h"
#include "../constants.hpp"


pk::WaterShader::WaterShader(

) : shader(pk::gShaderPool.get_shader(SHADERS_PATH "wave.fs")) {
    constexpr float screen_size[2] = {pk::SCREEN_SIZE.x , pk::SCREEN_SIZE.y};

    this->secondsLoc = GetShaderLocation(this->shader, "seconds");
    this->freqXLoc = GetShaderLocation(this->shader, "freqX");
    this->freqYLoc = GetShaderLocation(this->shader, "freqY");
    this->ampXLoc = GetShaderLocation(this->shader, "ampX");
    this->ampYLoc = GetShaderLocation(this->shader, "ampY");
    this->speedXLoc = GetShaderLocation(this->shader, "speedX");
    this->speedYLoc = GetShaderLocation(this->shader, "speedY");

    this->freqX = 15.0f;
    this->freqY = 15.0f;
    this->ampX = 3.0f;
    this->ampY = 3.0f;
    this->speedX = 3.0f;
    this->speedY = 3.0f;

    SetShaderValue(this->shader, GetShaderLocation(shader, "size"), &screen_size, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, freqXLoc, &this->freqX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, freqYLoc, &this->freqY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampXLoc, &this->ampX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampYLoc, &this->ampY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, speedXLoc, &this->speedX, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, speedYLoc, &this->speedY, SHADER_UNIFORM_FLOAT);
}


void pk::WaterShader::update_seconds(const float dt) {
    this->seconds += dt;
    SetShaderValue(shader, secondsLoc, &seconds, SHADER_UNIFORM_FLOAT);
}


void pk::WaterShader::begin_shader_mode() const {
    BeginShaderMode(this->shader);
}


void pk::WaterShader::end_shader_mode() const {
    EndShaderMode();
}
