#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include "CircleCollider.hpp"

class ObstacleEntity {
    public:
        ObstacleEntity(float radius, sf::Vector2f position);
        void update(float deltaTime);
        void render(sf::RenderTarget& renderTarget);
        bool collides(sf::Vector2f pos);

        sf::Vector2f getCenter();

    private:
        sf::CircleShape m_shape;
        CircleCollider m_collider;
};