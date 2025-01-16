#include "Scene.hpp"


pk::TitleScreen::TitleScreen() : pk::Scene(pk::TestScene1ID) {

}


void pk::TitleScreen::update(const float dt) {
    pk::Scene::update(dt);    
}


void pk::TitleScreen::draw() {
    pk::Scene::draw();
}
