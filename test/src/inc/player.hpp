#ifndef RPG_PLAYER_HPP
#define RPG_PLAYER_HPP

#include <cmath>

#include <teabag/entity.hpp>

class RPG;

class Player {
public:
	Player();
	Player(teabag::Entity entity);

	void setMovementGoal(int x, int y);

	void tick();
	void onCollision(sf::FloatRect e1, sf::FloatRect e2, teabag::Collision coll);

private:
	friend class RPG;

	teabag::Entity e;

	int moveSpeed;
	int goalX, goalY;

}; // class Player;

#endif // RPG_PLAYER_HPP
