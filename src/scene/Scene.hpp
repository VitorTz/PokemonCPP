#pragma once
#include <memory>
#include <iostream>
#include "SceneID.hpp"
#include "../constants.hpp"


namespace pk {

    class Scene {

    public:
        virtual ~Scene() = default;
        virtual void update(float dt) = 0;
        virtual void draw() = 0;

    };

    class SceneManager {

    private:
        std::unique_ptr<pk::Scene> scene{};
        pk::SceneID current_scene_id{pk::MAIN_SCENE};
        pk::SceneID next_scene_id{pk::MAIN_SCENE};
        bool should_change_scene{};

    private:
        void load_next_scene();

    public:
        void init();
        void change_scene(pk::SceneID scene_id);
        void update(float dt);
        void draw();

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
