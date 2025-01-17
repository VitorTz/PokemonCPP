#pragma once
#include "ECS.hpp"
#include "../constants.hpp"


namespace pk {

    class EcsManager {

    private:
        std::unordered_map<pk::SceneID, std::unique_ptr<pk::ECS>> ecs_map{};
        pk::ECS* current_ecs{};

    public:
        void init() {
            for (int i = 0; i < pk::NumScenes; i++) {
                this->ecs_map.emplace(
                    static_cast<pk::SceneID>(i),
                    std::make_unique<pk::ECS>()
                );
            }
            this->current_ecs = this->ecs_map[pk::MAIN_SCENE].get();
        }

        pk::ECS* get_ecs(const pk::SceneID scene_id) {
            return this->ecs_map[scene_id].get();
        }

        pk::ECS* get_current_ecs() {
            return this->current_ecs;
        }

        void set_current_ecs(const pk::SceneID scene_id) {
            this->current_ecs = this->ecs_map[scene_id].get();
        }

        void update(const float dt) const {
            this->current_ecs->update(dt);
        }

        void draw() const {
            this->current_ecs->draw();
        }

    };

    inline pk::EcsManager gEcsManager{};
    
} // namespace pk
