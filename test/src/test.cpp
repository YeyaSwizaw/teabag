#include "inc/test.hpp"

int main(int argc, char* argv[]) {
	teabag::Game g;
	g.init();

	g.addEventCallback(sf::Event::Closed, [&](sf::Event e){g.quit();});
	g.addEventCallback(sf::Event::KeyPressed, [](sf::Event e){std::cout << "Key Pressed: " << e.key.code << "\n";});

	g.run();

} // int main(int argc, car* argv);
