#ifndef TEABAG_SPRITEMAN_HPP
#define TEABAG_SPRITEMAN_HPP

#include "defines.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

TEABAG_NAMESPACE_BEGIN

class SpriteManager {
public:
	SpriteManager();

	int loadSpritesheet(std::string name);

	sf::Texture* getSpritesheet(std::string name);
	sf::Vector2i getSpriteSize(std::string name);

private:
	std::unordered_map<std::string, sf::Texture> sheets;
	std::unordered_map<std::string, sf::Vector2i> sizes;

}; // class SpriteManager;

TEABAG_NAMESPACE_END

#endif // TEABAG_SPRITEMAN_HPP
