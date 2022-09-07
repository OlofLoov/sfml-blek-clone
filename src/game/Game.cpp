#include "Game.hpp"
#include <iostream>
#include <math.h>
#include <random>

Game::Game() {

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;

    _window->create(sf::VideoMode(1600, 1200),"Wormy stuff", sf::Style::Titlebar, settings);
    _window->setFramerateLimit(144); 
    _window->setVerticalSyncEnabled(false);

    m_scenes.push(std::make_unique<WormyScene>(_window));
    m_isDrawing = false;
    m_hasCollided = false;

    m_trail = sf::VertexArray();
    m_trail.setPrimitiveType(sf::PrimitiveType::LinesStrip);

    m_line = sf::VertexArray();
    m_line.setPrimitiveType(sf::PrimitiveType::TrianglesStrip);

    m_moveDelta = sf::Vector2f();
    m_deltaTime = 0.0f;
    m_hasSetMoveParams = false;

    sf::CircleShape m_obstacle1;
    sf::CircleShape m_obstacle2;
    sf::CircleShape m_obstacle3;
    sf::CircleShape m_obstacle4;
    sf::CircleShape m_obstacle5;
    sf::CircleShape m_obstacle6;
    sf::CircleShape m_obstacle7;
    sf::CircleShape m_obstacle8;


    m_obstacle1 = sf::CircleShape(25.f);
    m_obstacle1.setFillColor(sf::Color::Black);
    m_obstacle1.setPosition(sf::Vector2f(150.f, 600.f));

    m_obstacle2 = sf::CircleShape(25.f);
    m_obstacle2.setFillColor(sf::Color::Black);
    m_obstacle2.setPosition(sf::Vector2f(350.f, 600.f));

    m_obstacle3 = sf::CircleShape(25.f);
    m_obstacle3.setFillColor(sf::Color::Black);
    m_obstacle3.setPosition(sf::Vector2f(550.f, 600.f));

    m_obstacle4 = sf::CircleShape(25.f);
    m_obstacle4.setFillColor(sf::Color::Black);
    m_obstacle4.setPosition(sf::Vector2f(750.f, 600.f));

    m_obstacle6 = sf::CircleShape(25.f);
    m_obstacle6.setFillColor(sf::Color::Black);
    m_obstacle6.setPosition(sf::Vector2f(950.f, 600.f));

    m_obstacle5 = sf::CircleShape(25.f);
    m_obstacle5.setFillColor(sf::Color::Black);
    m_obstacle5.setPosition(sf::Vector2f(1150.f, 600.f));

        m_obstacle7 = sf::CircleShape(25.f);
    m_obstacle7.setFillColor(sf::Color::Black);
    m_obstacle7.setPosition(sf::Vector2f(1350.f, 600.f));



    m_obstacles.push_back(m_obstacle1);
    m_obstacles.push_back(m_obstacle2);
    m_obstacles.push_back(m_obstacle3);
    m_obstacles.push_back(m_obstacle4);
    m_obstacles.push_back(m_obstacle5);
    m_obstacles.push_back(m_obstacle6);
    m_obstacles.push_back(m_obstacle7);
}

void Game::run() {   
    while (_window->isOpen()) {
        update();
        render();
    }
}

void Game::update() {
    sf::Event event;
    m_dt = m_clock.restart().asSeconds();

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window->close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) 
            _window->close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
             _window->close();


        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto mousePos = sf::Mouse::getPosition(*_window);
            if (!m_isDrawing && !m_hasCollided) {
                // start time to indicate that we started at this point
                m_isDrawing = true;
                m_drawPositions.clear();
                m_hasSetMoveParams = false;

                // insert first item
                auto drawPosition = DrawPosition(mousePos, m_TimeClock.getElapsedTime());
                m_drawPositions.emplace_back(drawPosition);  

            } else if (!m_hasCollided) {
                auto lastPos = m_drawPositions.back().position;

                if (!(mousePos.x == lastPos.x && mousePos.y == lastPos.y)) {
                    auto drawPosition = DrawPosition(mousePos, m_TimeClock.getElapsedTime());
                    m_drawPositions.emplace_back(drawPosition);            
                }  
  
            }
        } else {
            m_isDrawing = false;
            if (m_drawPositions.size() == 0) {
                m_hasCollided = false;
            }            
        }
    }

    m_trail.clear();

    // if collided with obstacle
    if (m_line.getVertexCount() > 0) {
        // assuming static obstacles the the first vertecies will collide with the obstacle before any other
        auto lastPos = m_line[m_line.getVertexCount() -1].position;
        auto drawPos = m_drawPositions.back().position;

        for(auto& obs : m_obstacles) {
            if (obs.getGlobalBounds().contains(drawPos) || obs.getGlobalBounds().contains(lastPos)) {
                m_hasCollided = true;
            }   
        }  
    }

    if(m_isDrawing || m_hasCollided) {
        m_drawPositions.erase(std::remove_if(m_drawPositions.begin(), m_drawPositions.end(), 
                       [&](DrawPosition dp) { 
                        auto currentTimeStamp = m_TimeClock.getElapsedTime().asSeconds();
                        auto timeStamp = dp.timeStamp.asSeconds();
                        return currentTimeStamp - 2.0f > timeStamp;
        }), m_drawPositions.end());
    } else {

        std::deque<DrawPosition> itemsToMove;
        std::deque<DrawPosition> items;
        auto currentTimeStamp = m_TimeClock.getElapsedTime().asSeconds();
        for(auto& v : m_drawPositions) {
            auto timeStamp = v.timeStamp.asSeconds();
            auto hasElapsed = currentTimeStamp - 2.0f > timeStamp;       
            if (hasElapsed) {
                itemsToMove.emplace_back(v);
            } else {
                items.emplace_back(v);
            }
        }

        if (!m_hasSetMoveParams && itemsToMove.size() > 0 && items.size() > 0) {
            m_hasSetMoveParams = true;
            auto firstOfItemsToMove = itemsToMove.front();
            auto lastElement = items.back();

            auto posDiff = sf::Vector2f(lastElement.position.x - firstOfItemsToMove.position.x, lastElement.position.y - firstOfItemsToMove.position.y);
            auto timeDiff = lastElement.timeStamp.asMicroseconds() - firstOfItemsToMove.timeStamp.asMicroseconds();
            m_moveDelta = posDiff;
            m_deltaTime = timeDiff;                    
        }

        if (itemsToMove.size() > 0 && items.size() > 0) {
            for(auto& v : itemsToMove) {
                v.position = sf::Vector2f(v.position.x + m_moveDelta.x, v.position.y + m_moveDelta.y);
                v.timeStamp = sf::microseconds(v.timeStamp.asMicroseconds() + m_deltaTime);
                items.emplace_back(v);                   
            }
            m_drawPositions.clear();
            m_drawPositions = items;
        }       
    }


    for(auto& v : m_drawPositions) {
        m_trail.append(v.position);
    }

    if (!this->m_scenes.empty())
        m_scenes.top()->update(m_dt);
}

void Game::drawRectangles()
{
    m_line.clear();

    sf::Vector2f p0;
    sf::Vector2f p1;

    float prevMag = 0.0f;

    for(int i = 1; i < m_drawPositions.size(); i++) {
        auto prev = m_drawPositions[i - 1];
        auto curr = m_drawPositions[i];

        auto v_distance = sf::Vector2f(curr.position.x - prev.position.x, curr.position.y - prev.position.y);
        float distance = sqrt(v_distance.x * v_distance.x + v_distance.y * v_distance.y);

        if (distance == 0)
            continue;

        auto v_distance_normalized = sf::Vector2f(v_distance.x / distance, v_distance.y / distance);
        auto v_perpendicular = sf::Vector2f(-v_distance_normalized.y, v_distance_normalized.x);

        float d = distance;

        // magnitude must be larger than 2.0
        // must not differ more than 50% of prevMag
        // must not be larger than 8

        float min = fmax(2.0, prevMag * 0.9f);
        float max = fmin(8.0f, prevMag * 1.1f);
        float magnitude = fmax(min, fmin(max, d));

        if ( p0.x == 0 && p1.x == 0 && p0.y == 0 && p1.y == 0) {
            p0 = sf::Vector2f(prev.position.x - v_perpendicular.x * magnitude, prev.position.y - v_perpendicular.y * magnitude);
            p1 = sf::Vector2f(prev.position.x + v_perpendicular.x * magnitude, prev.position.y + v_perpendicular.y * magnitude);
        }

        auto p2 = sf::Vector2f(curr.position.x - v_perpendicular.x * magnitude, curr.position.y - v_perpendicular.y * magnitude);
        auto p3 = sf::Vector2f(curr.position.x + v_perpendicular.x * magnitude, curr.position.y + v_perpendicular.y * magnitude);

        sf::Vertex v0;
        v0.position = p0;
        v0.color = sf::Color::Black;

        sf::Vertex v1;
        v1.position = p1;
        v1.color = sf::Color::Black;

        sf::Vertex v2;
        v2.position = p2;
        v2.color = sf::Color::Black;

        sf::Vertex v3;
        v3.position = p3;
        v3.color = sf::Color::Black;

        m_line.append(v0);
        m_line.append(v1);
        m_line.append(v2);
        m_line.append(v3);

        p0 = p2;
        p1 = p3;
        prevMag = magnitude;
    }

    _window->draw(m_line);
}

void Game::render() {
    _window->clear(sf::Color(255.f, 255.f, 255.f, 1.0f));
    if (!this->m_scenes.empty())
        m_scenes.top()->render();
    _window->draw(m_trail);
    drawRectangles();
    for(auto& obs : m_obstacles) {
        _window->draw(obs);
    }
    _window->display();
}


/*

oopifie
obstacle sep class
line sep class
use the scene..
create a "obstacle / fruit " creator
create a first level

polish line width

*/