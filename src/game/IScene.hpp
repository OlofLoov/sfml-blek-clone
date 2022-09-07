#pragma once

#include <SFML/Graphics.hpp>

class IScene {
    public:
        virtual ~IScene(){};
        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;
        virtual void initialize() = 0;
        virtual void onEvent(sf::Event event) = 0;
};
