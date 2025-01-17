#include "Camera.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include "../ecs/EcsManager.hpp"

pk::Camera::Camera() {
    for (pk::zindex_t z = pk::CAMERA_ZINDEX_MIN; z < pk::CAMERA_ZINDEX_MAX; z++) {
        this->entities[z].reserve(pk::MAX_ENTITIES);
    }
}

void pk::Camera::insert(const pk::entity_t e, const pk::zindex_t zindex) {
    if (this->is_on_camera[e] == false) {
        this->is_on_camera[e] = true;
        this->entities[zindex].emplace_back(0.0f, e);
        this->mSize++;
    }
}

void pk::Camera::erase(const pk::entity_t e, const pk::zindex_t zindex) {
    if (this->is_on_camera[e] == true) {
        this->is_on_camera[e] = false;
        std::vector<std::pair<float, pk::entity_t>>& vec = this->entities[zindex];
        auto iter = vec.begin();
        for (std::size_t i = 0; i < vec.size(); i++) {
            if (vec[i].second == e) {
                std::advance(iter, i);
                vec.erase(iter);
                this->mSize--;
                return;
            }
        }
    }
}


void pk::Camera::draw(pk::SystemManager* system_manager) {
    pk::ECS* ecs = pk::gEcsManager.get_current_ecs();
    this->begin_drawing();
        for (auto&[zindex, entities_vec] : this->entities) {
            for (auto&[centerY, entity] : entities_vec) {
                const pk::Transform& transform = ecs->get_transform(entity);
                centerY = transform.pos.y + transform.size.y / 2.0f;
            }
            std::sort(entities_vec.begin(), entities_vec.end());
            system_manager->draw(entities_vec);
        }
    this->end_drawing();
}

void pk::Camera::add_zoom(const float zoom) {
    this->camera2D.zoom = std::clamp(
        this->camera2D.zoom + zoom,
        pk::CAMERA_ZOOM_MIN,
        pk::CAMERA_ZOOM_MAX
    );
}


void pk::Camera::set_zoom(const float zoom) {
    this->camera2D.zoom = std::clamp(
        zoom,
        pk::CAMERA_ZOOM_MIN,
        pk::CAMERA_ZOOM_MAX
    );
}


float pk::Camera::get_zoom() const {
    return this->camera2D.zoom;
}


void pk::Camera::set_max_x_pos(const float x) {
    assert(x >= pk::SCREEN_CENTER.x);
    this->max_x_pos = x;
}

void pk::Camera::set_max_y_pos(const float y) {
    assert(y >= pk::SCREEN_CENTER.y);
    this->max_y_pos = y;
}


void pk::Camera::set_target(const float x, const float y) {
    this->camera2D.target.x = std::clamp(
        std::roundf(x),
        pk::SCREEN_CENTER.x,
        this->max_x_pos
    );
    this->camera2D.target.y = std::clamp(
        std::roundf(y),
        pk::SCREEN_CENTER.y,
        this->max_y_pos
    );
}


float pk::Camera::get_target_x() const {
    return this->camera2D.target.x;
}


float pk::Camera::get_target_y() const {
    return this->camera2D.target.y;
}


void pk::Camera::move(const float x, const float y) {
    this->set_target(
        this->camera2D.target.x + x, 
        this->camera2D.target.y + y
    );
}


void pk::Camera::clear() {
    for (auto& pair : this->entities) {
        pair.second.clear();
    }
    this->mSize = 0;
}


void pk::Camera::reset() {
    this->camera2D = Camera2D{
        pk::SCREEN_CENTER,
        pk::SCREEN_CENTER,
        0.0f, 
        1.0f
    };
    this->max_x_pos = std::numeric_limits<float>::max();
    this->max_y_pos = std::numeric_limits<float>::max();
    this->clear();
}


void pk::Camera::handle_user_input(const float dt) {
    this->add_zoom(GetMouseWheelMove() * dt * 2.0f);
}


void pk::Camera::begin_drawing() const {
    BeginMode2D(this->camera2D);
}


void pk::Camera::end_drawing() const {
    EndMode2D();
}
