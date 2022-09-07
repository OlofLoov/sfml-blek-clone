#include "LineEntity.hpp"
#include <math.h>

void LineEntity::update(const std::deque<InputPosition>& positions) {
    m_line = sf::VertexArray();
    m_line.setPrimitiveType(sf::PrimitiveType::TrianglesStrip);
    m_line.clear();

    sf::Vector2f p0;
    sf::Vector2f p1;

    float prevMag = 0.0f;

    for(int i = 1; i < positions.size(); i++) {
        auto prev = positions[i - 1];
        auto curr = positions[i];

        // get the distance 
        auto v_distance = sf::Vector2f(curr.position.x - prev.position.x, curr.position.y - prev.position.y);
        float distance = sqrt(v_distance.x * v_distance.x + v_distance.y * v_distance.y);

        if (distance == 0)
            continue;

        // normalize and as we know the perpendicular vector will be (-y,x)
        auto v_distance_normalized = sf::Vector2f(v_distance.x / distance, v_distance.y / distance);
        auto v_perpendicular = sf::Vector2f(-v_distance_normalized.y, v_distance_normalized.x);

        // magnitude must be larger than 2.0
        // must not differ more than 50% of prevMag
        // must not be larger than 8

        float min = fmax(2.0, prevMag * 0.8f);
        float max = fmin(10.0f, prevMag * 1.2f);
        float magnitude = fmax(min, fmin(max, distance));

        // if p0/p1 not initialized. only when i is 1. 
        if ( p0.x == 0 && p1.x == 0 && p0.y == 0 && p1.y == 0) { 
            p0 = sf::Vector2f(
                prev.position.x - v_perpendicular.x * magnitude, 
                prev.position.y - v_perpendicular.y * magnitude
            );

            p1 = sf::Vector2f(
                prev.position.x + v_perpendicular.x * magnitude, 
                prev.position.y + v_perpendicular.y * magnitude
            );
        }

        auto p2 = sf::Vector2f(
            curr.position.x - v_perpendicular.x * magnitude, 
            curr.position.y - v_perpendicular.y * magnitude
        );
        auto p3 = sf::Vector2f(
            curr.position.x + v_perpendicular.x * magnitude, 
            curr.position.y + v_perpendicular.y * magnitude
        );

        sf::Vertex v0(p0, sf::Color::Black);
        sf::Vertex v1(p1, sf::Color::Black);
        sf::Vertex v2(p2, sf::Color::Black);
        sf::Vertex v3(p3, sf::Color::Black);

        m_line.append(v0);
        m_line.append(v1);
        m_line.append(v2);
        m_line.append(v3);

        // using prev points for next iteration
        p0 = p2; 
        p1 = p3;
        prevMag = magnitude;
    }
}

void LineEntity::render(sf::RenderTarget& renderTarget) {
    renderTarget.draw(m_line);
}