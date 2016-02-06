#ifndef HANDGUN_H
#define HANDGUN_H


#include <math.h>
#include <cmath>

#include "SFML/Graphics.hpp" 

class Handgun {

public:
	Handgun();
	Handgun( sf::Texture &bulletTexture, sf::Vector2f crosshairPos, sf::Vector2f playerPos);
	void Update();
	sf::Sprite getSprite();
	sf::Vector2f getVelocity();
	sf::Vector2f getPosition();
	bool getAlive();
	void setAlive(bool j);
	sf::CircleShape Handgun::getCircleCol();


private:
	sf::CircleShape bulletCircle;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f crosshairPosition;
	sf::Vector2f Direction;
	sf::Sprite bulletSprite;
	float speed = 10;
	int time = 0;
	
	bool alive;
};

#endif
