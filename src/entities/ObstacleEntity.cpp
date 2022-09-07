#include "ObstacleEntity.hpp"
#include <math.h>

ObstacleEntity::ObstacleEntity(float radius, sf::Vector2f position) {
    m_shape.setFillColor(sf::Color::Black);
    m_shape.setRadius(radius);
    m_shape.setPosition(position);
}

sf::Vector2f ObstacleEntity::getCenter() {
    auto shapePos = m_shape.getPosition();
    shapePos.x += m_shape.getRadius();
    shapePos.y += m_shape.getRadius();

    return shapePos;
}

void ObstacleEntity::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(m_shape);
}

void ObstacleEntity::update(float deltaTime) { }

// using box colliding for circle. obv not optimal but it will do
bool ObstacleEntity::collides(sf::Vector2f pos) {
    return m_collider.collides(pos, m_shape);
}