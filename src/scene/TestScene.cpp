#include "Scene.hpp"


static std::unordered_map<pk::entity_t, float> speed{};


pk::TestScene::TestScene(): pk::Scene(pk::TestSceneID) {
    pk::ECS* ecs = pk::gEcsManager.get_ecs(pk::TestSceneID);

    for (int i = 0; i < pk::MAX_ENTITIES; i++) {
        const pk::entity_t e = ecs->sprite_create(
            1,
            ICONS_PATH "Atrox.png",
            GetRandomValue(0.0, pk::SCREEN_WIDTH),
            GetRandomValue(0.0f, pk::SCREEN_HEIGHT) - pk::SCREEN_HEIGHT
        );
        speed[e] = GetRandomValue(20.0f, 200.0f);
    }
}


void pk::TestScene::update(const float dt) {
    pk::ECS* ecs = pk::gEcsManager.get_ecs(pk::TestSceneID);
    const pk::SystemManager* system_manager = ecs->get_system_manager();
    const std::set<pk::entity_t>& sprite_entities = system_manager->get_entities_by_system<Sprite>();
    for (const pk::entity_t e : sprite_entities) {
        pk::Transform& transform = ecs->get_transform(e);
        transform.pos.y += dt * speed[e];
        if (transform.pos.y > pk::SCREEN_HEIGHT) {
            ecs->entity_destroy(e);
        }
    }
    pk::Scene::update(dt);
}


void pk::TestScene::draw() {
    pk::Scene::draw();
}
