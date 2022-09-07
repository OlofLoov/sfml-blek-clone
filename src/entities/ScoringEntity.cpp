#include "ScoringEntity.hpp"
#include <iostream>
#include <math.h>

ScoringEntity::ScoringEntity(sf::Vector2f position) {
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setRadius(25.f);
    m_shape.setPosition(position);
    m_scale = 1.0f;
}

sf::Vector2f ScoringEntity::getCenter() {
    auto shapePos = m_shape.getPosition();
    shapePos.x += m_shape.getRadius();
    shapePos.y += m_shape.getRadius();

    return shapePos;
}

void ScoringEntity::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(m_shape);
}

void ScoringEntity::reset() {
    m_scale = 1.0f;
    m_shape.setScale(sf::Vector2f(m_scale, m_scale));
    m_taken = false;
}

void ScoringEntity::update(float deltaTime) {
    if (!m_taken && m_scale - deltaTime > 0.0f)
        return;

    m_scale = m_scale - deltaTime;
    m_shape.scale(sf::Vector2f(m_scale, m_scale));
 }

bool ScoringEntity::collides(sf::Vector2f pos) {
    return m_collider.collides(pos, m_shape);
}

void ScoringEntity::take() {
    m_taken = true;
}
