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

    if (!this->m_scenes.empty())
        m_scenes.top()->update(m_dt);
}

void Game::render() {
    _window->clear(sf::Color(255.f, 255.f, 255.f, 1.0f));
    if (!this->m_scenes.empty())
        m_scenes.top()->render();

    _window->display();
}
