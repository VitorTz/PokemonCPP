#include "Scene.hpp"


pk::Scene::Scene(const pk::SceneID scene_id) : scene_id(scene_id) {
    pk::ECS* ecs = pk::gEcsManager.get_ecs(scene_id);
    if (ecs->is_empty() == false) {
        return;
    }
    pk::read_tiled_map(pk::MAP_PATH_BY_SCENE_ID[scene_id], ecs);
}


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