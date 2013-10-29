#ifndef TEABAG_GAME_HPP
#define TEABAG_GAME_HPP

#include "defines.hpp"
#include "eventmanager.hpp"

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
	 * Constructs an empty Game object.
	 * This does not acually load anything. init() must be called to initialise
	 * the class properly.
	 */
	Game();

	/**
	 * Initialises the game.
	 * This reads the main game definition file, and initialises the window
	 * and optionally loads the first map.
	 *
	 * @param loadMapNow If true, loads the first map after initialising the
	 * window.
	 * @return Negative on failure, 0 on success.
	 */
	int init(bool loadMapNow = false);

	/**
	 * Adds an event callback.
	 * Adds a function to be called whenever an event of the specified type
	 * is fired.
	 *
	 * @param eventType The event type the function is to be registered with.
	 * @param callback The function to be called.
	 * @return Negative on failure, 0 on success.
	 */
	int addEventCallback(sf::Event::EventType eventType, std::function<void(sf::Event)> callback);

	/**
	 * Runs the game.
	 * Starts the main loop, calling tick callbacks every loop, event callbacks
	 * when the relevant events happen, and collision callbacks when the 
	 * relevant objects collide.
	 *
	 * @return Negative on error, 0 on clean exit.
	 */
	int run();

	/**
	 * Ends the game.
	 */
	void exit();

private:
	sf::RenderWindow gameWind;

	EventManager eventManager;

}; // class Game;

TEABAG_NS_END

#endif // TEABAG_GAME_HPP
