#include "inc/test.hpp"

Test::Test() {

} // Test::Test();

int Test::run() {
	if(g.init() < 0) {
		return -1;

	} // if(g.init() < 0);

	g.addEventCallback(sf::Event::Closed, [&](sf::Event e){g.quit();});
	g.addEventCallback(sf::Event::KeyPressed, [](sf::Event e){std::cout << "Key Pressed: " << e.key.code << "\n";});
	g.addEventCallback(sf::Event::KeyPressed, std::bind(&Test::moveEntity, this, std::placeholders::_1));

	g.addCollisionCallback("test", [&](std::string s){g.getEntity("test")->move(lastDelta * -1.0f);});

	g.addTickCallback(std::bind(&Test::onTick, this));

	g.run();

	return 0;

} // int Test::run();

void Test::moveEntity(sf::Event e) {
	sf::Vector2f d;
	if(e.key.code == sf::Keyboard::Up) {
		d.x = 0;
		d.y = -1;

	} // if(e.key.code == sf::Keyboard::Up);
	else if(e.key.code == sf::Keyboard::Down) {
		d.x = 0;
		d.y = 1;

	} // else if(e.key.code == sf::Keyboard::Down);
	else if(e.key.code == sf::Keyboard::Left) {
		d.x = -1;
		d.y = 0;

	} // else if(e.key.code == sf::Keyboard::Left);
	else if(e.key.code == sf::Keyboard::Right) {
		d.x = 1;
		d.y = 0;

	} // else if(e.key.code == sf::Keyboard::Right);

	g.getEntity("test")->move(d * 5.0f);

	lastDelta = d;

} // void Test::moveEntity(sf::Event e);

void Test::onTick() {
	if(g.isKeyDown(sf::Keyboard::Space)) {
		std::cout << "SPAAAAAAAAAAAAAACE\n";

	} // if(g.isKeyDown(sf::Keyboard::Space));

} // void Test::onTick();

int main(int argc, char* argv[]) {
	Test t;

	return t.run();

} // int main(int argc, car* argv);
