#pragma once
#include <SFML/Graphics.hpp>
#include "CircleCollider.hpp"

class ScoringEntity {
    public:
        ScoringEntity(sf::Vector2f position);
        void update(float deltaTime);
        void render(sf::RenderTarget& renderTarget);
        bool collides(sf::Vector2f pos);
        void take();
        void reset();
        sf::Vector2f getCenter();

    private:
        sf::CircleShape m_shape;
        float m_scale;
        bool m_taken;
        CircleCollider m_collider;
};