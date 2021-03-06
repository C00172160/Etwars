#ifndef BLOCK_H
#define BLOCK_H

#include "CollisionManager.h"
#include "SFML/Graphics.hpp"
#include <string.h>
#include <Box2D\Box2D.h>

class Block {

public:
	Block();
	Block(char c, sf::Vector2f position, b2World& world);
	void createBlock(b2World& world, sf::Vector2f position); 
	void Update(sf::CircleShape& circle2);
	bool getAlive();
	b2Body* getBody();
	sf::CircleShape& getCircle();

private:
	char type;
	sf::Vector2f m_position;
	sf::String GrassSymbols = "1";
	sf::String DirtSymbols = "2";
	b2Fixture* SensorFixture;
	bool alive = true;
	b2Body * BlockBody;
	sf::CircleShape circle;
};

#endif
