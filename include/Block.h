#ifndef BLOCK_H
#define BLOCK_H

#include "CollisionManager.h"
#include "SFML/Graphics.hpp"
#include <string.h>
#include <Box2D\Box2D.h>

class Block {

public:
	Block();
	Block(int c, sf::Vector2f position, b2World& world);
	void createBlock(b2World& world, sf::Vector2f position, int type);
	void Block::CheckLives();
	bool getAlive();
	b2Body* getBody();
	sf::RectangleShape& getRect();
	sf::CircleShape& getCircle();

private:
	int type;
	int lives;
	sf::Vector2f m_position;
	b2Fixture* SensorFixture;
	bool alive = true;
	b2Body * BlockBody;
	sf::RectangleShape blockRectangle;
	sf::CircleShape blockCirlce;
	
};

#endif
