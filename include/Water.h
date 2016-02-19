#ifndef WATER_H
#define WATER_H

#include "CollisionManager.h"
#include "SFML/Graphics.hpp"
#include <string.h>
#include "game.hpp"


class Water {

public:

	Water();
	void updateWater();
	void setPositon(sf::Vector2f pos);
	void Draw(Game* game);
	
	

private:
	sf::Vector2f position;
	int m_Startpoint;
	int timer1;
	int timer2;
	int timer3;
	int timer4;
	int timer5;
	int timer6;
	int timer7;
	int source1;
	int source2;
	int source3;
	int source4;
	int source5;
	int source6;
	int source7;

	sf::Texture watertex;
	sf::Texture seatex;
	sf::Sprite sprite1;
	sf::Sprite sprite2;
	sf::Sprite sprite3;
	sf::Sprite sprite4;
	sf::Sprite sprite5;
	sf::Sprite sprite6;
	sf::Sprite sprite7;
	sf::Sprite sea;
	
};

#endif
