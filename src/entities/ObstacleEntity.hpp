#include <SFML/Graphics.hpp>
#include <deque>

class ObstacleEntity {
    public:
        ObstacleEntity(float radius, sf::Vector2f position);
        void update(float deltaTime);
        void render(sf::RenderTarget& renderTarget);
        bool collides(sf::Vector2f pos);

    private:
        sf::CircleShape m_shape;
};