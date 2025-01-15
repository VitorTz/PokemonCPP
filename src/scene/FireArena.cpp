#include "Scene.hpp"


pk::FireArenaScene::FireArenaScene() : pk::Scene(pk::FireArenaSceneID) {

}


void pk::FireArenaScene::update(const float dt) {
    pk::Scene::update(dt);
}


void pk::FireArenaScene::draw() {
    pk::Scene::draw();
}
