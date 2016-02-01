#include "Handgun.h"

Handgun::Handgun()
{
}

Handgun::Handgun( sf::Texture &bulletTexture,sf::Vector2f crosshairPos,sf::Vector2f playerPos)
{

	position = crosshairPos;
	crosshairPosition = crosshairPos;
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setOrigin((bulletSprite.getGlobalBounds().width / 2), (bulletSprite.getGlobalBounds().height / 2));


	Direction = crosshairPos - (sf::Vector2f(playerPos.x, playerPos.y));
	float length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));
	Direction = Direction / length;
	velocity = Direction * speed;
}


void Handgun::Update()
{
	time ++;
	if (time > 10)
	{
		alive = false;
	}
	position += velocity ;
	bulletSprite.setPosition(position);

}

sf::Sprite Handgun::getSprite()
{
	return bulletSprite;
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