#include "Scene.hpp"


pk::TitleScreen::TitleScreen() : pk::Scene(pk::TestSceneID) {

}


void pk::TitleScreen::update(const float dt) {
    pk::Scene::update(dt);
}


void pk::TitleScreen::draw() {
    pk::Scene::draw();
}
