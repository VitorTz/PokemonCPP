#include "Camera.hpp"
#include <algorithm>
#include <cassert>


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
        x,
        pk::SCREEN_CENTER.x,
        this->max_x_pos
    );
    this->camera2D.target.y = std::clamp(
        y,
        pk::SCREEN_CENTER.y,
        this->max_y_pos
    );
}


void pk::Camera::move(const float x, const float y) {
    this->set_target(
        this->camera2D.target.x + x, 
        this->camera2D.target.y + y
    );
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
}


void pk::Camera::begin_drawing() const {
    BeginMode2D(this->camera2D);
}


void pk::Camera::end_drawing() const {
    EndMode2D();
}