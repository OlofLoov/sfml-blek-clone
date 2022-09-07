#include <SFML/Graphics.hpp>

class ScoringEntity {
    public:
        ScoringEntity(sf::Vector2f position);
        void update(float deltaTime);
        void render(sf::RenderTarget& renderTarget);
        bool collides(sf::Vector2f pos);
        void take();
        void reset();

    private:
        sf::CircleShape m_shape;
        float m_scale;
        bool m_taken;
};