#include "inc/test.hpp"

Test::Test() {

} // Test::Test();

int Test::run() {
	if(g.init(true) < 0) {
		return -1;

	} // if(g.init() < 0);

	g.onClose(std::bind(&teabag::Game::exit, &g));

	player = g.getEntity("test");
	g.onKey(sf::Keyboard::Up, std::bind(&teabag::Entity::move, &player, 0, -5));
	g.onKey(sf::Keyboard::Down, std::bind(&teabag::Entity::move, &player, 0, 5));
	g.onKey(sf::Keyboard::Left, std::bind(&teabag::Entity::move, &player, -5, 0));
	g.onKey(sf::Keyboard::Right, std::bind(&teabag::Entity::move, &player, 5, 0));
	player.onCollision(std::bind(&Test::playerCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	return g.run();

} // int Test::run();

void Test::playerCollision(sf::FloatRect e1, sf::FloatRect e2, teabag::Collision coll) {
	if(coll.collision.width <= coll.collision.height) {
		if(e1.left <= e2.left) {
			player.move(-1, 0);

		} // if(e1.left <= e2.left);
		else {
			player.move(1, 0);

		} // else;

	} // if(coll.width <= coll.height);
	else {
		if(e1.top <= e2.top) {
			player.move(0, -1);

		} // if(e1.top <= e2.top);
		else {
			player.move(0, 1);

		} // else;

	} // else;

} // void Test::playerCollision(sf::FloatRect e1, sf::FloatRect e2, sf::FloatRect coll);

int main(int argc, char* argv[]) {
	Test t;

	return t.run();

} // int main(int argc, car* argv);
