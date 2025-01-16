#include "Scene.hpp"


static std::unordered_map<pk::entity_t, float> speed{};


pk::TestScene1::TestScene1(): pk::Scene(pk::TestScene1ID) {
    pk::ECS* ecs = pk::gEcsManager.get_ecs(pk::TestScene1ID);

    if (ecs->is_empty() == false) {
        return;
    }

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


void pk::TestScene1::update(const float dt) {
    pk::ECS* ecs = pk::gEcsManager.get_ecs(pk::TestScene1ID);
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
    if (IsKeyPressed(KEY_SPACE)) {
        pk::gSceneManager.change_scene(pk::TestScene2ID);
    }
}


void pk::TestScene1::draw() {
    pk::Scene::draw();
}
