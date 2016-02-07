#ifndef SNIPER_H
#define SNIPER_H

#include "Handgun.h"
#include <math.h>
#include <cmath>

#include "SFML/Graphics.hpp" 

class Sniper : public  Handgun
{

public:
	Sniper();
	Sniper(sf::Texture &bulletTexture, sf::Vector2f crosshairPos, sf::Vector2f playerPos);


private:

};

#endif
