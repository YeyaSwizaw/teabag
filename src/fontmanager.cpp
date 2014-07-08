#include "inc/fontmanager.hpp"

TEABAG_NS

TEABAG_INTERNAL

void FontManager::queueFont(std::string name, std::string font, int size) {
    queue.push_back({name, font, size});
}

void FontManager::loadQueue() {
    fontFiles.clear();
    fonts.clear();

    for(FontInfo& info : queue) {
        loadFont(info);
    } 

    queue.clear();
} 

void FontManager::loadFont(FontInfo& info) {
    if(fontFiles.find(info.font) == fontFiles.end()) {
        std::string file = TEABAG_FONT(info.font);
        sf::Font font;
        if(!font.loadFromFile(file)) {
            throw teabag::FileOpenError(file);
        } 

        fontFiles[info.font] = font;
    } 

    fonts[info.name] = info;
} 

TEABAG_INTERNAL_END

TEABAG_NS_END
