#include "Scene.hpp"


pk::HouseScene::HouseScene() : pk::Scene(pk::HospitalSceneID) {

}


void pk::HouseScene::update(const float dt) {
    pk::Scene::update(dt);
}


void pk::HouseScene::draw() {
    pk::Scene::draw();
}
