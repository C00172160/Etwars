#include "Shotgun.h"

Shotgun::Shotgun()
{
}

Shotgun::Shotgun(sf::Texture &bulletTexture, sf::Vector2f crosshairPos, sf::Vector2f playerPos, float  angleProjection)
{

	position = crosshairPos;
	crosshairPosition = crosshairPos;
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setOrigin((bulletSprite.getGlobalBounds().width / 2), (bulletSprite.getGlobalBounds().height / 2));
	bulletCircle.setRadius((bulletTexture.getSize().x) / 2);

	Direction = crosshairPos - (sf::Vector2f(playerPos.x, playerPos.y));
	float length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));
	Direction = Direction / length;
	bulletCircle.setPosition(position.x - bulletCircle.getRadius(), position.y - bulletCircle.getRadius());
	bulletCircle.setFillColor(sf::Color::Black);
	Direction.x = Direction.x * cos(angleProjection) - Direction.y * sin(angleProjection);
	Direction.y = Direction.x * sin(angleProjection) + Direction.y * cos(angleProjection);
	velocity = Direction * speed;
}




