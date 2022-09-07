#pragma once

#include <SFML/Graphics.hpp>

struct InputPosition {
    InputPosition(sf::Vector2f pos, sf::Time ts) {
        position = pos;
        timeStamp = ts;
    }

    InputPosition(sf::Vector2i pos, sf::Time ts) {
        position = sf::Vector2f(pos.x, pos.y);
        timeStamp = ts;
    }

    bool shoudRender;
    sf::Vector2f position;
    sf::Time timeStamp;
};