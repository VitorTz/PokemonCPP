#include "Scene.hpp"


pk::WaterArenaScene::WaterArenaScene() : pk::Scene(WaterArenaSceneID) {

}


void pk::WaterArenaScene::update(const float dt) {
    pk::Scene::update(dt);
}


void pk::WaterArenaScene::draw() {
    pk::Scene::draw();
}
