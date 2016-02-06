#ifndef CROSSHAIR_H
#define CROSSHAIR_H
#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>
#include "Player.h"
#include "SFML/Graphics.hpp" 

class Crosshair {

public:
	Crosshair();
	Crosshair(sf::Texture& tex, sf::Vector2f pos, sf::Texture& handguntex, sf::Texture& Rockettex, sf::Texture& shotguntex, sf::Texture& snipertex );
	void Update(sf::Vector2f playerPos, int guntype, Player& player);
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	void Init(sf::Texture& tex, sf::Vector2f pos, sf::Texture& handguntex, sf::Texture& Rockettex, sf::Texture& shotguntex, sf::Texture& snipertex);
	sf::Sprite getGunSprite();

private:
	sf::Sprite handgun, rocketLauncher, shotgun, sniper,currentgunSprite;
	sf::Sprite Sprite;
	sf::Vector2f gunPosition;
	sf::Vector2f m_position;
	float angle =0;
	float gunoffset;
	float rotation = 0;

};

#endif



