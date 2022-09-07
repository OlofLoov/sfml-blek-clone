#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Scenes.hpp"
#include "IScene.hpp"
#include <memory>
#include <stack>
#include <deque>

class WormyScene;

struct DrawPosition {

    DrawPosition(sf::Vector2f pos, sf::Time ts) {
        position = pos;
        timeStamp = ts;
    }

    DrawPosition(sf::Vector2i pos, sf::Time ts) {
        position = sf::Vector2f(pos.x, pos.y);
        timeStamp = ts;
    }

    bool shoudRender;
    sf::Vector2f position;
    sf::Time timeStamp;
};

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

        std::deque<DrawPosition> m_drawPositions;
        bool m_isDrawing;
        bool m_hasCollided;
        void drawRectangles();
        sf::VertexArray m_trail;

        sf::VertexArray m_line;

        std::vector<sf::CircleShape> m_obstacles;
};

