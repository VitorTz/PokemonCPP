#include "System.hpp"
#include "../EcsManager.hpp"
#include "../../shaders/WaterShader.hpp"


void pk::WaterSystem::update(const float dt) {
    this->water_shader.update_seconds(dt);
    if (IsKeyDown(KEY_F)) {
        this->water_shader.speedX += 1;
    }
}


void pk::WaterSystem::draw(const pk::entity_t e) {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();
    this->water_shader.begin_shader_mode();
        const pk::Water& water = ecs->get_component<pk::Water>(e);
        const pk::Transform& transform = ecs->get_transform(e);
        DrawTextureV(water.texture, transform.pos, WHITE);
    this->water_shader.end_shader_mode();
}