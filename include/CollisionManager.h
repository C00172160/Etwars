#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "SFML/Graphics.hpp"
#include <vector>
#include "CollisionManager.h"


class CollisionManager {

public:

	static bool CircleDetectCollision(sf::CircleShape &s1, sf::CircleShape &s2);
	static bool CircleRectangleCollision(sf::CircleShape &s1, sf::RectangleShape &s2);
	static bool RectangleRectangleCollision(sf::RectangleShape &s1, sf::RectangleShape &s2);
	static float dotProduct(sf::Vector2f v1, sf::Vector2f v2);
	static sf::Vector2f NormaliseVector(sf::Vector2f v1);

private:


};

#endif
