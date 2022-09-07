#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <memory>
#include <stack>
#include <deque>
#include "InputPosition.hpp"

class LineEntity {
    public:
        void update(const std::deque<InputPosition>& positions);
        void render(sf::RenderTarget& renderTarget);
        
    private:
        sf::VertexArray m_line;
};