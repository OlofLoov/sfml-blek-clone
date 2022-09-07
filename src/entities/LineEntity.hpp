#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <stack>
#include <deque>
#include "InputPosition.hpp"
#include <tuple>

class LineEntity {
    public:
        LineEntity();
        void update(const std::deque<InputPosition>& positions);
        void render(sf::RenderTarget& renderTarget);
        std::vector<sf::Vector2f> getLatestVertices();

    private:
        sf::VertexArray m_line;
};