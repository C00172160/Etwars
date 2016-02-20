#include "Water.h"



Water::Water()
{

}


void Water::Init(bool lava)
{
	source1 = 0;
	source2 = 1;
	source3 = 2;
	source4 = 3;
	source5 = 4;
	source6 = 5;
	source7 = 6;
	if (lava == true)
	{


		watertex.loadFromFile("Resources/lava.png");
		seatex.loadFromFile("Resources/lavasea.png");
	}
	else
	{
		watertex.loadFromFile("Resources/water.png");
		seatex.loadFromFile("Resources/sea.png");
	}
	sea.setTexture(seatex);
	sprite1.setTexture(watertex);
	sprite2.setTexture(watertex);
	sprite3.setTexture(watertex);
	sprite4.setTexture(watertex);
	sprite5.setTexture(watertex);
	sprite6.setTexture(watertex);
	sprite7.setTexture(watertex);


}
void Water::setPositon(sf::Vector2f pos)
{
	position = pos;
	sea.setPosition(pos + sf::Vector2f(0,46));
		
}

void Water::updateWater()
{
	timer1++;
	if (timer1 >= 5)
	{
		source1++;
		if (source1 > 7){
			source1 = 0;
		}
		timer1 = 0;
	}
	timer2++;
	if (timer2 >= 5)
	{
		source2++;
		if (source2 > 7){
			source2 = 0;
		}
		timer2 = 0;
	}
	timer3++;
	if (timer3 >= 5)
	{
		source3++;
		if (source3 > 7){
			source3 = 0;
		}
		timer3 = 0;
	}
	timer4++;
	if (timer4 >= 5)
	{
		source4++;
		if (source4 > 7){
			source4 = 0;
		}
		timer4 = 0;
	}
	timer5++;
	if (timer5 >= 5)
	{
		source5++;
		if (source5 > 7){
			source5 = 0;
		}
		timer5 = 0;
	}
	timer6++;
	if (timer6 >= 5)
	{
		source6++;
		if (source6 > 7){
			source6 = 0;
		}
		timer6 = 0;
	}
	timer7++;
	if (timer7 >= 5)
	{
		source7++;
		if (source7 > 7){
			source7 = 0;
		}
		timer7 = 0;
	}

	sprite1.setTextureRect(sf::IntRect(source1 * 101, 0, 101, 46));
	sprite1.setPosition(position);

	sprite2.setTextureRect(sf::IntRect(source2 * 101, 0, 101, 46));
	sprite2.setPosition(position + sf::Vector2f(101,0));

	sprite3.setTextureRect(sf::IntRect(source3 * 101, 0, 101, 46));
	sprite3.setPosition(position + sf::Vector2f(202, 0));

	sprite4.setTextureRect(sf::IntRect(source4 * 101, 0, 101, 46));
	sprite4.setPosition(position + sf::Vector2f(303, 0));

	sprite5.setTextureRect(sf::IntRect(source5 * 101, 0, 101, 46));
	sprite5.setPosition(position + sf::Vector2f(404, 0));

	sprite6.setTextureRect(sf::IntRect(source6 * 101, 0, 101, 46));
	sprite6.setPosition(position + sf::Vector2f(505, 0));

	sprite7.setTextureRect(sf::IntRect(source7 * 101, 0, 101, 46));
	sprite7.setPosition(position + sf::Vector2f(606, 0));
}
void Water::Draw(Game* game)
{
	game->window.draw(sprite1);
	game->window.draw(sprite2);
	game->window.draw(sprite3);
	game->window.draw(sprite4);
	game->window.draw(sprite5);
	game->window.draw(sprite6);
	game->window.draw(sprite7);
	game->window.draw(sea);


}



