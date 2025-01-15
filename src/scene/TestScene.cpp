#include "Scene.hpp"


pk::TestScene::TestScene(): pk::Scene(pk::TestSceneID) {

}


void pk::TestScene::update(const float dt) {
    pk::Scene::update(dt);
}


void pk::TestScene::draw() {
    pk::Scene::draw();
}
