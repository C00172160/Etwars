#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Handgun.h"
#include <math.h>
#include <cmath>

#include "SFML/Graphics.hpp" 

class Shotgun : public  Handgun 
{

public:
	Shotgun();
	Shotgun(sf::Texture &bulletTexture, sf::Vector2f crosshairPos, sf::Vector2f playerPos,float angleProjection);


private:
	
};

#endif
