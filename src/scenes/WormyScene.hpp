#pragma once

#include "IScene.hpp"
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "LineEntity.hpp"
#include "InputPosition.hpp"
#include "ObstacleEntity.hpp"
#include "ScoringEntity.hpp"

class WormyScene: public IScene {
    public:
        WormyScene(std::shared_ptr<sf::RenderWindow> window);
        ~WormyScene() {
            std::cout<<"Destorying WormyScene" << std::endl;
        };
        
        void update(float deltaTime);
        void render();
        void initialize();
        void onEvent(sf::Event event);
    
    private:
        std::shared_ptr<sf::RenderWindow> _window;

        bool m_isDrawing; // if currently drawing
        bool m_hasCollided; // if collided during drawing, don't allow more drawing
        bool m_hasSetMoveParams; // bool indicating wheter or not the move parameters have been set. 
        // Move params are static for for the "worm". such as delta position and delta time.
        // move params are set once the user stops drawing

        std::deque<InputPosition> m_drawPositions;
        LineEntity m_line;
        sf::Clock m_clock; // used for timing 
        sf::Vector2f m_moveDelta; 

        std::vector<ObstacleEntity> m_obstacles;
        std::vector<ScoringEntity> m_scorings;
        bool m_isDirty; // indicating wheter to reset/initialize scene once again
        float m_deltaTime;

        bool isOutOfBounds();
        void checkCollisions();

        void updateScorings(float deltaTime);
        void updateObstacles(float deltaTime);

        void filterOldPositions(float time); // remove items that been in the array longer than time
        void reset();
};