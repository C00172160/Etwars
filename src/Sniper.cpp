#include "Sniper.h"

Sniper::Sniper()
{
}

Sniper::Sniper(sf::Texture &bulletTexture, sf::Vector2f crosshairPos, sf::Vector2f playerPos)
{
	ttl = 100;
	speed = 15;
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
	velocity = Direction * speed;
	angle = atan2(Direction.y, Direction.x);
	bulletSprite.setRotation((angle / M_PI) * 180.0);
}




