#include "inc/game.hpp"

TEABAG_NS

void Game::init() {
    std::string file = TEABAG_MAIN_FILE;

    // Open file reader
    internal::Reader reader(file);
    if(!reader) {
        throw FileOpenError(file);
    } 

    std::string name = TEABAG_DEFAULT_NAME;
    unsigned int width = TEABAG_DEFAULT_WINDOW_W;
    unsigned int height = TEABAG_DEFAULT_WINDOW_H;

    // Parse main file
    while(reader.nextLine()) {
        std::string option;
        if(!reader.get(option)) {
            throw LineReadError(file, reader.line);
        } 

        if(option == "name") {
            name = reader.line.substr(5);
        }
        else if(option == "wind") {
            if(!reader.get(width, height)) {
                throw LineReadError(file, reader.line);
            } 
        } 
    } 

    // Create SFML window
    window.create(sf::VideoMode(width, height), name);

    // #FIXME
    window.setFramerateLimit(60);
}

GameSignals& Game::signals() {
    return sigs;
} 

World& Game::world() {
    return w;
} 

void Game::run() {
    while(window.isOpen()) {
        if(w.justLoaded) {
            w.justLoaded = false;
        }

        sigs.tick().call();

        sf::Event e;
        while(window.pollEvent(e)) {
            if(w.justLoaded) {
                break;
            } 

            sigs.handleEvent(e);
        } 

        if(w.justLoaded) {
            continue;
        } 

        w.checkCollisions();

        if(w.justLoaded) {
            continue;
        } 

        window.clear();
        w.render(window);
        window.display();
    } 
} 

void Game::resizeView(int w, int h) {
    window.setView(sf::View({0, 0, (float)w, (float)h}));
} 

void Game::exit() {
    window.close();
} 

TEABAG_NS_END
