#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Scenes.hpp"
#include "IScene.hpp"
#include <memory>
#include <stack>
#include <deque>
#include "LineEntity.hpp"

class WormyScene;

class Game {
    public:
        Game();
        ~Game() {
            std::cout << "Destroying Game" << std::endl;
        };

        void run();

    private:
        void render();
        void update();

        float m_dt;
        sf::Clock m_clock;
        sf::Clock m_TimeClock;
        sf::Vector2f m_moveDelta;
        float m_deltaTime;
        bool m_hasSetMoveParams;

        std::shared_ptr<sf::RenderWindow> _window = std::make_shared<sf::RenderWindow>();
        std::stack<std::unique_ptr<IScene>> m_scenes;

        bool m_isDrawing;
        bool m_hasCollided;

        std::deque<InputPosition> m_drawPositions;
        sf::VertexArray m_line;

        std::vector<sf::CircleShape> m_obstacles;
};

