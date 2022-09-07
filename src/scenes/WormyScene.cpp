#include "WormyScene.hpp"
#include <math.h>

WormyScene::WormyScene(std::shared_ptr<sf::RenderWindow> window) {
    _window = window;
    initialize();
}

void WormyScene::initialize() {
    std::cout << "GameState::initialize" << std::endl;
    m_isDirty = false;
    m_obstacles.clear();
    m_scorings.clear();

    auto ob1 = ObstacleEntity(50.f, sf::Vector2f(300.f, 500.f));
    auto ob2 = ObstacleEntity(50.f, sf::Vector2f(700.f, 500.f));
    auto ob3 = ObstacleEntity(50.f, sf::Vector2f(1100.f, 500.f));

    m_obstacles.push_back(ob1);
    m_obstacles.push_back(ob2);
    m_obstacles.push_back(ob3);

    auto s1 = ScoringEntity(sf::Vector2f(525.f, 525.f));
    auto s2 = ScoringEntity(sf::Vector2f(925.f, 525.f));
    auto s3 = ScoringEntity(sf::Vector2f(1325.f, 525.f));

    m_scorings.push_back(s1);
    m_scorings.push_back(s2);
    m_scorings.push_back(s3);

    reset();
}

void WormyScene::reset() {
    m_drawPositions.clear();
    m_moveDelta = sf::Vector2f();
    m_deltaTime = 0.0f;
    m_hasSetMoveParams = false;
    m_hasCollided = false;

    for(auto& s : m_scorings) 
        s.reset();
}

void WormyScene::onEvent(sf::Event event) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        auto mousePos = sf::Mouse::getPosition(*_window);

        if (!m_isDrawing && !m_hasCollided) {
            reset();
            m_isDrawing = true;
            m_drawPositions.clear();
            m_hasSetMoveParams = false;
            m_isDirty = true;

            // insert first item
            auto drawPosition = InputPosition(mousePos, m_clock.getElapsedTime());
            m_drawPositions.emplace_back(drawPosition);  

        } else if (!m_hasCollided) {

            auto lastPos = m_drawPositions.back().position;
            // don't add same pos multiple times, will cause issues when determining distance between points
            if (!(mousePos.x == lastPos.x && mousePos.y == lastPos.y)) {
                auto drawPosition = InputPosition(mousePos, m_clock.getElapsedTime());
                m_drawPositions.push_back(drawPosition);            
            }  
        }
    } else {
        if (m_isDrawing) {
            // once stopped drawing we reschedule the time positions
            // thus we don't need to wait time_delay. 
            // since we filter the array based on m_timeDelay we know that the oldest element is roughly m_timedelay
            auto oldest = m_drawPositions.front();
            auto minTime = m_clock.getElapsedTime() - sf::seconds(m_timeDelay);
            auto dt = minTime.asSeconds() - oldest.timeStamp.asSeconds();

            for(auto& dp : m_drawPositions) {
                dp.timeStamp = dp.timeStamp + sf::seconds(dt);
            }

            m_isDrawing = false;
        }
        
        if (m_drawPositions.size() == 0 && m_isDirty) {
            reset();
        }
    }
}

void WormyScene::checkCollisions() {
    if (m_hasCollided)
        return;

    if(m_drawPositions.size() == 0) {
        return;
    }
    auto lastPos = m_drawPositions.back().position;
    auto positionsToCheck = m_line.getLatestVertices();
    positionsToCheck.push_back(lastPos);

    sf::Vector2f collisionPosition;

    for(auto& p : positionsToCheck) {
        for(auto& obs : m_obstacles) {
            if (obs.collides(p)) {
                m_hasCollided = true;
                collisionPosition = obs.getCenter();
                break;
            }
        }

        // while drawing it is not allowed to collide with "score points"
        if(m_isDrawing) {
            for(auto& s : m_scorings) {
                if (s.collides(p)) {
                    m_hasCollided = true;
                    collisionPosition = s.getCenter();
                    break;
                }
            }
        } else { // check collisions when not drawing -> points!!
            for(auto& s : m_scorings) {
                if (s.collides(p)) {
                    s.take();          
                    break;
                }
            }
        }
    }

    if (m_hasCollided) {
        // avoid glitchy line rendering when colliding by addings new pos to center of collision obj 
        auto drawPosition = InputPosition(collisionPosition, m_drawPositions.back().timeStamp + sf::milliseconds(100));
        m_drawPositions.push_back(drawPosition);
    }
}

void WormyScene::update(float deltaTime) {
    if(m_drawPositions.size() > 0) {
        checkCollisions();

        if (isOutOfBounds()) {
            reset();
        }
    }
        
    if(m_isDrawing || m_hasCollided) {
        filterOldPositions(m_timeDelay);
    } else {
        std::deque<InputPosition> itemsToMove;
        std::deque<InputPosition> items;
        auto currentTimeStamp = m_clock.getElapsedTime();
        for(auto& v : m_drawPositions) {
            auto hasElapsed = currentTimeStamp - sf::seconds(m_timeDelay) > v.timeStamp;       
            if (hasElapsed) {
                itemsToMove.push_back(v);
            } else {
                items.push_back(v);
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

    updateObstacles(deltaTime);
    updateScorings(deltaTime);

    m_line.update(m_drawPositions);
}

void WormyScene::filterOldPositions(float time) {
    auto currentTimeStamp = m_clock.getElapsedTime().asSeconds();

    m_drawPositions.erase(std::remove_if(m_drawPositions.begin(), m_drawPositions.end(), 
                    [&](InputPosition dp) { 
                    auto timeStamp = dp.timeStamp.asSeconds();
                    return currentTimeStamp - m_timeDelay > timeStamp;
    }), m_drawPositions.end());
}

void WormyScene::updateScorings(float deltaTime) {
    for(auto& s : m_scorings) 
        s.update(deltaTime);
}

void WormyScene::updateObstacles(float deltaTime) {
    for(auto& ob : m_obstacles) 
        ob.update(deltaTime);
}

bool WormyScene::isOutOfBounds() {
    //out of bounds 
    bool oob = true;
    for(auto& p : m_drawPositions) {
        auto w = _window->getSize().x;
        auto h = _window->getSize().y;

        if(!(p.position.x > w || p.position.y > h || p.position.x < 0 || p.position.y < 0)) {
            oob = false;
            break;
        }
    }

    return oob;
}

void WormyScene::render() {
    m_line.render(*_window);

    for(auto& ob : m_obstacles) 
        ob.render(*_window);

    for(auto& s : m_scorings) 
        s.render(*_window);
}