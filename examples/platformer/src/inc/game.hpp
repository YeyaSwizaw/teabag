#ifndef PLATFORMER_GAME_HPP
#define PLATFORMER_GAME_HPP

#include "teabag/game.hpp"
#include "teabag/collision.hpp"

#include <string>
#include <functional>
#include <algorithm>
#include <iostream>
#include <unordered_set>

#include <SFML/Window.hpp>

class Game {
public:
    void run();

private:
    static const float BOUNCE_FACTOR;
    static const float ACCEL;
    static const float MAX_SPEED;
    static const float JUMP_SPEED;
    static const float GRAVITY;
    static const float MAX_FALL;

    void tick();
    void playerCollision(teabag::Collision coll);
    void key(sf::Keyboard::Key key, bool press);
    void levelLoaded(std::string name);

    void resetBoosts();
    void resetBounces();

    std::string current;

    float xSpeed, ySpeed;
    bool up, left, right, reset;
    bool jumped;

    std::unordered_set<std::string> usedBoosts, usedBounces;

    teabag::Game game;
};

const float Game::BOUNCE_FACTOR = 1.3;
const float Game::ACCEL = 0.5;
const float Game::MAX_SPEED = 3;
const float Game::JUMP_SPEED = 6.5;
const float Game::GRAVITY = 0.5;
const float Game::MAX_FALL = 5;

#endif
