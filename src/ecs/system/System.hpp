#pragma once
#include <raylib.h>
#include <raymath.h>
#include <set>
#include "../../util/types.hpp"
#include "../../shaders/WaterShader.hpp"


namespace pk {

    class System {

    public:
        std::set<pk::entity_t> entities{};

    public:
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void draw(pk::entity_t e) = 0;

    };

    class TransformSystem final : public System {

    public:
        void update(float dt) override { }
        void draw(pk::entity_t e) override { }

    };

    class SpriteSystem final : public System {

    public:
        void update(float dt) override { }
        void draw(pk::entity_t e) override;

    };

    class SpriteAnimationSystem final : public System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class PlayerSystem final : public System {

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override { }

    };

    class WaterSystem final : public System {

    private:
        pk::WaterShader water_shader{};

    public:
        void update(float dt) override;
        void draw(pk::entity_t e) override;

    };

    class TransitionSystem final : public System {

    public:
        void update(float dt) override { }
        void draw(pk::entity_t e) override;

    };
    
} // namespace pk
