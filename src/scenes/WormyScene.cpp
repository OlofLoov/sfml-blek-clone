#include "WormyScene.hpp"

WormyScene::WormyScene(std::shared_ptr<sf::RenderWindow> window)
{
    _window = window;
    initialize();
}

void WormyScene::initialize()
{
    std::cout << "GameState::initialize" << std::endl;
}

void WormyScene::update(float deltaTime) {
}

void WormyScene::render() {
}