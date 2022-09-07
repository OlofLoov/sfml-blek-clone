#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>

class CircleCollider {
    public:
        bool collides(sf::Vector2f pos, sf::CircleShape& shape);
};