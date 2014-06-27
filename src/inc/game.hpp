#ifndef TEABAG_GAME_HPP
#define TEABAG_GAME_HPP
 
#include "defines.hpp"
#include "error.hpp"
#include "reader.hpp"
#include "signal.hpp"
#include "world.hpp"

#include <SFML/Graphics.hpp>

TEABAG_NS

/**
 * The base class for a game.
 * This class is the starting point for anything created with the teabag
 * engine. It contains functions to manage initialisation, events, entities,
 * and the game map.
 */
class Game {
public:
	/**
	 * Initialises the game.
	 * This reads the main game definition file, and initialises the window.
     * 
     * @throws Error on failure - error reading file, initialising SFML etc. 
	 */
    void init();

    /**
     * Returns the attached signals struct.
     */
    GameSignals& signals();

    /**
     * Returns a reference to the world object, for access to the map, entities
     * etc.
     */
    World& world();

    /**
	 * Runs the game.
	 * Starts the main loop, calling tick callbacks every loop, event callbacks
	 * when the relevant events happen, and collision callbacks when the 
	 * relevant objects collide.
     */
    void run();

    /**
     * Resizes the window view.
     * Generally to be called when the window is resized.
     */
    void resizeView(int w, int h);

    /**
     * Exits the game
     */
    void exit();

private:
    sf::RenderWindow window;
    GameSignals sigs;
    World w;
};

TEABAG_NS_END

#endif
