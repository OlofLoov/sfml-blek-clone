#pragma once

#include "IScene.hpp"
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>

class WormyScene: public IScene {
    public:
        WormyScene(std::shared_ptr<sf::RenderWindow> window);
        ~WormyScene() {
            std::cout<<"Destorying WormyScene" << std::endl;
        };
        
        void update(float deltaTime);
        void render();
        void initialize();
    
    private:
        std::shared_ptr<sf::RenderWindow> _window;

};