#include "inc/player.hpp"

Player::Player() {

} // Player::Player();

Player::Player(teabag::Entity entity) 
	: e(entity), moveSpeed(5), goalX(e.getX()), goalY(e.getY()) {

} // Player::Player(Entity entity);

void Player::setMovementGoal(int x, int y) {
	goalX = x;
	goalY = y;

} // void Player::setMovementGoal(int x, int y);

void Player::tick() {
	int x = e.getX();
	int y = e.getY();

	if(abs(x - goalX) > 5 || abs(y - goalY) > 5) {
		double xd = goalX - x;
		double yd = goalY - y;
	
		double mag = sqrt(pow(xd, 2) + pow(yd, 2));

		xd /= mag;
		yd /= mag;

		e.move(xd * moveSpeed, yd * moveSpeed);

	} // if(x != goalX || y != goalY);

} // void Player::tick();

void Player::onCollision(sf::FloatRect e1, sf::FloatRect e2, teabag::Collision coll) {
	if(coll.collision.width <= coll.collision.height) {
		if(e1.left <= e2.left) {
			e.move(-1, 0);

		} // if(e1.left <= e2.left);
		else {
			e.move(1, 0);

		} // else;

	} // if(coll.width <= coll.height);
	else {
		if(e1.top <= e2.top) {
			e.move(0, -1);

		} // if(e1.top <= e2.top);
		else {
			e.move(0, 1);

		} // else;

	} // else;

} // void Player::onCollision(sf::FloatRect e1, sf::FloatRect e2, teabag::Collision coll);
