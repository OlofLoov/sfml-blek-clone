#include "CircleCollider.hpp"

bool CircleCollider::collides(sf::Vector2f pos, sf::CircleShape& shape) {
    auto shapePos = shape.getPosition();
    shapePos.x += shape.getRadius();
    shapePos.y += shape.getRadius();

    auto v_distance = sf::Vector2f(shapePos.x - pos.x, shapePos.y - pos.y);
    float distance = sqrt(v_distance.x * v_distance.x + v_distance.y * v_distance.y);

    return distance < shape.getRadius();
}