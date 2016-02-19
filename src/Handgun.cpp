#include "Handgun.h"

Handgun::Handgun()
{
}

Handgun::Handgun( sf::Texture &bulletTexture,sf::Vector2f crosshairPos,sf::Vector2f playerPos)
{
	ttl = 30;
	speed = 10;
	position = crosshairPos;
	crosshairPosition = crosshairPos;
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setOrigin((bulletSprite.getGlobalBounds().width / 2), (bulletSprite.getGlobalBounds().height / 2));
	bulletCircle.setRadius((bulletTexture.getSize().x)/2);

	Direction = crosshairPos - (sf::Vector2f(playerPos.x, playerPos.y));
	float length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));
	Direction = Direction / length;
	velocity = Direction * speed;
	bulletCircle.setPosition(position.x - bulletCircle.getRadius(),position.y - bulletCircle.getRadius());
	bulletCircle.setFillColor(sf::Color::Black);




}


void Handgun::Update()
{
	time ++;
	if (time > ttl)
	{
		alive = false;
	}
	position += velocity ;
	bulletSprite.setPosition(position);
	bulletCircle.setPosition(position.x - bulletCircle.getRadius(), position.y - bulletCircle.getRadius());


	
}

sf::Sprite Handgun::getSprite()
{
	return bulletSprite;
}
sf::CircleShape Handgun::getCircleCol()
{
	return bulletCircle;
}

sf::Vector2f Handgun::getVelocity()
{
	return velocity;
}
sf::Vector2f Handgun::getPosition()
{
	return position;
}
bool Handgun::getAlive()
{
	return alive;
}
void Handgun::setAlive(bool j){

	alive = j;

}