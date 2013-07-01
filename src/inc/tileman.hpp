#ifndef TEABAG_TILEMAN_HPP
#define TEABAG_TILEMAN_HPP

#include "defines.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <memory>
#include <utility>

#include <SFML/Graphics.hpp>

TEABAG_NAMESPACE_BEGIN 

class TileManager {
public:
	TileManager();
	
	int loadTile(int r, int g, int b, std::string name);

	std::string getNameFromColour(sf::Color colour);
	sf::Texture* getTexFromName(std::string name);
	sf::Texture* getTexFromColour(sf::Color colour);

private:
	std::unordered_map<std::string, sf::Texture> texFromName;
	std::unordered_map<sf::Color, std::string, std::function<int(sf::Color)>> nameFromColour;

}; // class TileManager;

TEABAG_NAMESPACE_END

#endif // TEABAG_TILEMAN_HPP
