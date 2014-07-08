#ifndef TEABAG_FONTMANAGER_HPP
#define TEABAG_FONTMANAGER_HPP

#include "defines.hpp"
#include "error.hpp"

#include <string>
#include <vector>
#include <unordered_map>

#include <SFML/Graphics.hpp>

TEABAG_NS

class UI;

TEABAG_INTERNAL

struct FontInfo {
    std::string name, font;
    int size;
}; 

class FontManager {
private:
    friend class teabag::UI;

    void queueFont(std::string name, std::string font, int size);
    void loadQueue();
    void loadFont(FontInfo& info);

    std::vector<FontInfo> queue;

    std::unordered_map<std::string, sf::Font> fontFiles;
    std::unordered_map<std::string, FontInfo> fonts;
};

TEABAG_NS_END

TEABAG_INTERNAL_END

#endif
