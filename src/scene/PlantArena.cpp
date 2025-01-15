#include "Scene.hpp"


pk::PlantArenaScene::PlantArenaScene() : pk::Scene(pk::PlantArenaSceneID) {

}


void pk::PlantArenaScene::update(const float dt) {
    pk::Scene::update(dt);
}


void pk::PlantArenaScene::draw() {
    pk::Scene::draw();
}
