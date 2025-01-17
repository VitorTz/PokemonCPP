#include "System.hpp"
#include "../EcsManager.hpp"
#include <iostream>


void pk::TransitionSystem::draw(const pk::entity_t e) {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();
    const pk::Transition& transition = ecs->get_component<pk::Transition>(e);
    const pk::Transform& transform = ecs->get_transform(e);
    if (transition.is_hovered) {
        const Vector2 pos = GetScreenToWorld2D(
        {pk::SCREEN_CENTER.x, pk::SCREEN_HEIGHT - 40.0f},
            ecs->get_camera()->get_camera2D()
        );
        const char* txt = TextFormat("Press F to enter %s", pk::SCENE_NAMES[transition.scene_id]);
        constexpr float padding = 20.0f;
        const float txt_width = static_cast<float>(MeasureText(txt, 18));
        const float rect_width = txt_width + padding * 2.0f;
        DrawRectangleRec(
            {pos.x - rect_width / 2.0f, pos.y - 25.0f, rect_width, 50.0f},
            Color{0, 0, 0, 180}
        );
        DrawText(
            txt,
            pos.x - txt_width / 2,
            pos.y - 10.0f,
            18,
            WHITE
        );
    }
}
