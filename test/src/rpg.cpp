#include "inc/rpg.hpp"

RPG::RPG() {

} // RPG::RPG();

int RPG::run() {
	if(g.init(true) < 0) {
		return -1;

	} // if(g.init(true) < 0);

	g.onClose(std::bind(&teabag::Game::exit, &g));

	player = Player(g.getEntity("player"));
	player.e.onCollision(std::bind(&Player::onCollision, &player, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	g.onTick(std::bind(&Player::tick, &player));
	g.onMouseButtonRelease(std::bind(&RPG::mouseRelease, this, std::placeholders::_1));

	return g.run();

} // int RPG::run();

void RPG::mouseRelease(sf::Event e) {
	player.setMovementGoal(e.mouseButton.x, e.mouseButton.y);

} // void RPG::onMouseButtonRelease(sf::Event e);

int main(int argc, char* argv[]) {
	RPG rpg;

	return rpg.run();

} // int main(int argc, char* argv[]);
