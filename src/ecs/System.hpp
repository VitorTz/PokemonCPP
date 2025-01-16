#pragma once
#include <set>
#include "../util/types.hpp"
#include "../constants.hpp"


namespace pk {

    class System {    

    public:
        std::set<pk::entity_t> entities{};        

    public:
        virtual ~System() = default;
        virtual void update(float dt) = 0;
        virtual void draw() = 0;

    };

    class TransformSystem : public System {

    public:
        void update(float dt) override;
        void draw() override;

    };

    class SpriteSystem : public System {

    public:
        void update(float dt) override;
        void draw() override;

    };

    class SpriteAnimationSystem : public System {

    public:
        void update(float dt) override;
        void draw() override;

    };

    class PlayerSystem : public System {

    public:
        void update(float dt) override;
        void draw() override;

    };
    
} // namespace pk
