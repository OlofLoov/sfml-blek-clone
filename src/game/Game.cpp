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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
             _window->close();

        if (!this->m_scenes.empty())
            m_scenes.top()->onEvent(event);
    }

    // if collided with obstacle
   /* if (m_line.getVertexCount() > 0) {
        // assuming static obstacles the the first vertecies will collide with the obstacle before any other
        auto lastPos = m_line[m_line.getVertexCount() -1].position;
        auto drawPos = m_drawPositions.back().position;

        for(auto& obs : m_obstacles) {
            if (obs.getGlobalBounds().contains(drawPos) || obs.getGlobalBounds().contains(lastPos)) {
                m_hasCollided = true;
            }   
        }  
    } */

    if (!this->m_scenes.empty())
        m_scenes.top()->update(m_dt);
}

void Game::render() {
    _window->clear(sf::Color(255.f, 255.f, 255.f, 1.0f));
    if (!this->m_scenes.empty())
        m_scenes.top()->render();

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