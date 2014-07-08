#include "inc/game.hpp"

void Game::run() {
    lvl = 0;
    totalDeaths = 0;
    time = sf::Time::Zero;

    game.init();

    game.signals().close().connect(std::bind(&teabag::Game::exit, &game));
    game.signals().resize().connect(std::bind(&teabag::Game::resizeView, &game, std::placeholders::_1, std::placeholders::_2));
    game.signals().tick().connect(std::bind(&Game::tick, this));
    game.signals().keyPress().connect(std::bind(&Game::key, this, std::placeholders::_1, true));
    game.signals().keyRelease().connect(std::bind(&Game::key, this, std::placeholders::_1, false));
    game.world().signals().levelLoad().connect(std::bind(&Game::levelLoaded, this, std::placeholders::_1));

    game.world().loadLevel("lvl1");
    game.run();
} 

void Game::tick() {
    // Reset level (after 'r' or death
    if(reset) {
        game.world().loadLevel(current);
    } else {

        // Jump
        if(up && !jumped) {
            up = false;
            jumped = true;
            ySpeed = std::min(ySpeed, -JUMP_SPEED);
        } 

        // Apply gravity
        ySpeed += GRAVITY;
        ySpeed = std::min(MAX_FALL, ySpeed);

        // Apply horizontal acceleration
        if(left || right) {
            xSpeed += ACCEL;
        } else {
            xSpeed -= ACCEL;
        } 

        xSpeed = std::max(0.0f, xSpeed);
        xSpeed = std::min(MAX_SPEED, xSpeed);

        // Move
        game.world().entity("player").move(
            (left || right) ? (xSpeed * (left ? -1 : 1)) : 0, 
            ySpeed); // ySpeed should really be called yVeloctiy but OH WELL
    }
} 

void Game::playerCollision(teabag::Collision coll) {
    // Reached end of level
    if(coll.targetName == "goal") {
        if(coll.collisionBounds.width > 8 && coll.collisionBounds.height > 8) {
            sf::Time t = clock.getElapsedTime();
            std::cout << "Level " << lvl << ": " << t.asSeconds() << "s, " << deaths << " deaths" << std::endl;

            time += t;
            totalDeaths += deaths;

            if(game.world().option("next") == "win") {
                std::cout << "You Win!" << std::endl;
                std::cout << "Total: " << time.asSeconds() << "s, " << totalDeaths << " deaths" << std::endl;
                game.exit();
            } else {
                game.world().loadLevel(game.world().option("next"));

                lvl++;
                deaths = 0;
                clock.restart();
            }
        }
    } 
        
    // Boost
    else if(coll.targetName.find("boost") != std::string::npos) {
        if(usedBoosts.find(coll.targetName) == usedBoosts.end()) {
            jumped = false;

            usedBoosts.insert(coll.targetName);
            game.world().entity(coll.targetName).setSpriteCoord(1, 0);
        } 
    } 


    // Bounce
    else if(coll.targetName.find("bounce") != std::string::npos) {
        if(usedBounces.find(coll.targetName) == usedBounces.end()) {
            ySpeed = -BOUNCE_FACTOR * JUMP_SPEED;

            usedBounces.insert(coll.targetName);
            game.world().entity(coll.targetName).setSpriteCoord(1, 0);
        } 
    } 

    // Hit a spike
    else if(coll.targetName == "spike") {
        if(coll.collisionBounds.height > 4) {
            deaths++;
            reset = true;
        } 
    } 
    
    // Hit a wall
    else {
        if(coll.collisionBounds.height <= coll.collisionBounds.width) {
            if(game.world().entity("player").y() < coll.targetBounds.top) {
                ySpeed = 0;
                jumped = false;
                resetBoosts();
                resetBounces();

                game.world().entity("player").move(0, -coll.collisionBounds.height);
            } else {
                game.world().entity("player").move(0, coll.collisionBounds.height);
            } 
        } else {
            xSpeed = 0;
            game.world().entity("player").move(coll.collisionBounds.width * ((game.world().entity("player").x() < coll.targetBounds.left) ? -1 : 1), 0);
        } 
    }
} 

// Key press or release (bool is true if press, false if release)
void Game::key(sf::Keyboard::Key key, bool press) {
    switch(key) {
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            up = press;
            break;

        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            left = press;
            break;

        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            right = press;
            break;

        case sf::Keyboard::R:
            reset = press;
            break;

        default:
            break;
    } 
} 

void Game::levelLoaded(std::string name) {
    current = name;

    jumped = false;
    resetBoosts();
    resetBounces();

    up = false;
    left = false;
    right = false;
    reset = false;

    xSpeed = 0;
    ySpeed = 0;

    game.world().entity("player").signals().collision().connect(std::bind(&Game::playerCollision, this, std::placeholders::_1));
} 

void Game::resetBoosts() {
    for(std::string b : usedBoosts) {
        game.world().entity(b).setSpriteCoord(0, 0);
    } 
    usedBoosts.clear();
} 

void Game::resetBounces() {
    for(std::string b : usedBounces) {
        game.world().entity(b).setSpriteCoord(0, 0);
    } 
    usedBounces.clear();
} 

int main(int argc, char* argv[]) {
    Game g;
    g.run();
} 
