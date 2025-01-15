#include "Scene.hpp"


pk::Scene::Scene(const pk::SceneID scene_id) : scene_id(scene_id) {  }


void pk::Scene::update(const float dt) {
    pk::gEcsManager.set_current_ecs(this->scene_id);
    pk::gEcsManager.update(dt);
}


void pk::Scene::draw() {
    pk::gEcsManager.set_current_ecs(this->scene_id);
    pk::gEcsManager.draw();
}


pk::SceneID pk::Scene::get_scene_id() const {
    return this->scene_id;
}