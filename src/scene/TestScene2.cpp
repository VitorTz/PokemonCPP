#include "Scene.hpp"


pk::TestScene2::TestScene2() : pk::Scene(pk::TestScene2ID) {

}


void pk::TestScene2::update(const float dt) {
    pk::Scene::update(dt);
    if (IsKeyPressed(KEY_SPACE)) {
        pk::gSceneManager.change_scene(pk::TestScene1ID);
    }
}


void pk::TestScene2::draw() {
    pk::Scene::draw();
}
