#include "inc/test.hpp"

Test::Test() {

} // Test::Test();

int Test::run() {
	if(g.init(true) < 0) {
		return -1;

	} // if(g.init() < 0);

	g.addEventCallback(sf::Event::Closed, [this](sf::Event e) { g.exit(); });
	g.addEventCallback(sf::Event::KeyPressed, std::bind(&Test::keyPressed, this, std::placeholders::_1));

	return g.run();

} // int Test::run();

void Test::keyPressed(sf::Event e) {
	if(e.key.code == sf::Keyboard::Up) {
		g.scrollMap(0, -5);

	} // if(e.key.code == sf::Keyboard::Up);
	else if(e.key.code == sf::Keyboard::Down) {
		g.scrollMap(0, 5);

	} // else if(e.key.code == sf::Keyboard::Down);
	else if(e.key.code == sf::Keyboard::Left) {
		g.scrollMap(-5, 0);

	} // else if(e.key.code == sf::Keyboard::Left);
	else if(e.key.code == sf::Keyboard::Right) {
		g.scrollMap(5, 0);

	} // else if(e.key.code == sf::Keyboard::Right);
	else if(e.key.code == sf::Keyboard::Space) {
		g.getEntity("test")->move(10, 10);

	} // else if(e.key.code == sf::Keyboard::Space);

} // void Test::keyPressed(sf::Event e);

int main(int argc, char* argv[]) {
	Test t;

	return t.run();

} // int main(int argc, car* argv);
