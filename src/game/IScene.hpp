#pragma once

class IScene {
    public:
        virtual ~IScene(){};
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
        virtual void initialize() = 0;
};
