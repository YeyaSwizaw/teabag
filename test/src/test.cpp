#include "inc/test.hpp"

Test::Test() {

} // Test::Test();

int Test::run() {
	if(g.init() < 0) {
		return -1;

	} // if(g.init() < 0);

	g.addEventCallback(sf::Event::Closed, [this](sf::Event e) { g.exit(); });

	return g.run();

} // int Test::run();

int main(int argc, char* argv[]) {
	Test t;

	return t.run();

} // int main(int argc, car* argv);
