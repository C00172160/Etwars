#ifndef CROSSHAIR_H
#define CROSSHAIR_H
#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>

#include "SFML/Graphics.hpp" 

class Crosshair {

public:
	Crosshair();
	Crosshair(sf::Texture& tex,sf::Vector2f pos);
	void Update(sf::Vector2f playerPos);
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	void Init(sf::Texture& tex, sf::Vector2f pos);

private:
	sf::Sprite Sprite;
	sf::Vector2f m_position;
	float angle =0;
	float rotation = 0;
};

#endif



