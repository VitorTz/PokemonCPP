#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include "SceneID.hpp"
#include "../constants.hpp"
#include "../ecs/EcsManager.hpp"


namespace pk {

    class Scene {

    private:
        pk::SceneID scene_id{};

    public:
        explicit Scene(pk::SceneID scene_id);
        virtual ~Scene() = default;
        virtual void update(float dt);
        virtual void draw();
        pk::SceneID get_scene_id() const;

    };

    class SceneManager {

    private:
        std::unique_ptr<pk::Scene> scene{};
        pk::SceneID current_scene_id{pk::MAIN_SCENE};
        pk::SceneID next_scene_id{pk::MAIN_SCENE};
        std::map<std::string, std::string> scene_context{};
        bool should_change_scene{};

    private:
        void load_next_scene();

    public:
        void init();

        void change_scene(pk::SceneID scene_id);

        void update(float dt) const;
        void draw() const;

        std::map<std::string, std::string>* get_scene_context();

    };

    class TitleScreen : public pk::Scene {

    public:
        TitleScreen();
        void update(float dt) override;
        void draw() override;

    };


    class WorldScene : public pk::Scene {

    public:
        WorldScene();
        void update(float dt) override;
        void draw() override;

    };

    class FireArenaScene : public pk::Scene {

    public:
        FireArenaScene();
        void update(float dt) override;
        void draw() override;

    };

    class PlantArenaScene : public pk::Scene {

    public:
        PlantArenaScene();
        void update(float dt) override;
        void draw() override;

    };

    class WaterArenaScene : public pk::Scene {

    public:
        WaterArenaScene();
        void update(float dt) override;
        void draw() override;

    };

    class HospitalScene : public pk::Scene {

    public:
        HospitalScene();
        void update(float dt) override;
        void draw() override;

    };

    class HouseScene : public pk::Scene {

    public:
        HouseScene();
        void update(float dt) override;
        void draw() override;

    };

    class TestScene : public pk::Scene {

    public:
        TestScene();
        void update(float dt) override;
        void draw() override;

    };

    inline pk::SceneManager gSceneManager{};    

} // namespace pk
