#include "Scene.hpp"


void pk::SceneManager::load_next_scene() {
    switch (this->next_scene_id) {
        case pk::TitleScreenID:
            this->scene = std::make_unique<pk::TitleScreen>();
            break;
        case pk::WorldSceneID:
            this->scene = std::make_unique<pk::WorldScene>();
            break;
        case pk::FireArenaSceneID:
            this->scene = std::make_unique<pk::FireArenaScene>();
            break;
        case pk::PlantArenaSceneID:
            this->scene = std::make_unique<pk::PlantArenaScene>();
            break;
        case pk::WaterArenaSceneID:
            this->scene = std::make_unique<pk::WaterArenaScene>();
            break;
        case pk::HospitalSceneID:
            this->scene = std::make_unique<pk::HospitalScene>();
            break;
        case pk::HouseSceneID:
            this->scene = std::make_unique<pk::HouseScene>();
            break;
        case pk::TestSceneID:
            this->scene = std::make_unique<pk::TestScene>();
            break;
        default:
            break;
    }
    this->current_scene_id = this->next_scene_id;
    this->should_change_scene = false;
}


void pk::SceneManager::init() {
    this->load_next_scene();
}


void pk::SceneManager::change_scene(const pk::SceneID scene_id) {
    this->should_change_scene = true;
    this->next_scene_id = scene_id;
}


void pk::SceneManager::update(const float dt) {
    this->scene->update(dt);
}


void pk::SceneManager::draw() {
    this->scene->draw();
}
