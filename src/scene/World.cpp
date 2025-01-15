#include "Scene.hpp"


pk::WorldScene::WorldScene() : pk::Scene(WorldSceneID) {

}


void pk::WorldScene::update(const float dt) {
    pk::Scene::update(dt);
}


void pk::WorldScene::draw() {
    pk::Scene::draw();
}
