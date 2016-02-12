#include "Crosshair.h"

Crosshair::Crosshair()
{

}
Crosshair::Crosshair(sf::Texture& tex, sf::Vector2f pos, sf::Texture& handguntex, sf::Texture& Rockettex, sf::Texture& shotguntex, sf::Texture& snipertex)
{
	m_position = sf::Vector2f(pos.x + 30, pos.y + 30);
	tex.setSmooth(true);
	Sprite.setTexture(tex);
	handgun.setTexture(handguntex);
	rocketLauncher.setTexture(Rockettex);
	shotgun.setTexture(shotguntex);
	sniper.setTexture(snipertex);

	
}
void Crosshair::Init(sf::Texture& tex, sf::Vector2f pos, sf::Texture& handguntex, sf::Texture& Rockettex, sf::Texture& shotguntex, sf::Texture& snipertex)
{
	m_position = sf::Vector2f(pos.x, pos.y);
	tex.setSmooth(true);
	Sprite.setTexture(tex);
	Sprite.setTexture(tex);
	handgun.setTexture(handguntex);
	rocketLauncher.setTexture(Rockettex);
	shotgun.setTexture(shotguntex);
	sniper.setTexture(snipertex);
	spawnoffset = 0;
}

void Crosshair::Update(sf::Vector2f playerPos, int guntype, Player& player)
{
	gunPosition = playerPos;
	sf::Vector2f playerPosition = sf::Vector2f(playerPos.x  , playerPos.y  );
	Sprite.setOrigin(10.f, 10.f);

	m_position = sf::Vector2f(playerPosition.x +spawnoffset , playerPosition.y );
	
	Sprite.setPosition(m_position.x, m_position.y);

	float newx = cos(angle) *   (m_position.x - playerPosition.x) - sin(angle) * (m_position.y - playerPosition.y) + playerPosition.x;
	float newpy = sin(angle) * (m_position.x - playerPosition.x) + cos(angle) * (m_position.y - playerPosition.y) + playerPosition.y;

	m_position = sf::Vector2f(newx, newpy);

	drawposition = sf::Vector2f(playerPosition.x + gunoffset, playerPosition.y);
	float newdrawx = cos(angle) *   (drawposition.x - playerPosition.x) - sin(angle) * (drawposition.y - playerPosition.y) + playerPosition.x;
	float newdrawpy = sin(angle) * (drawposition.x - playerPosition.x) + cos(angle) * (drawposition.y - playerPosition.y) + playerPosition.y;
	drawposition = sf::Vector2f(newdrawx, newdrawpy);

	Sprite.setPosition(drawposition);


	if (guntype == 1)
	{
		spawnoffset = 100;
		currentgunSprite = rocketLauncher;
		gunoffset = 60;
	}
	else if (guntype == 2)
	{
		spawnoffset = 20;
		currentgunSprite = handgun;
		gunoffset = 60;
	}
	else if (guntype == 3)
	{
		spawnoffset = 20;
		currentgunSprite = shotgun;
		gunoffset = 60;
	}
	else if (guntype == 4)
	{
		spawnoffset = 20;
		currentgunSprite = sniper;
		gunoffset = 120;
	}


	currentgunSprite.setOrigin(currentgunSprite.getGlobalBounds().width / 2, currentgunSprite.getGlobalBounds().height / 2);
	currentgunSprite.setPosition(playerPos);
	currentgunSprite.setRotation(angle/M_PI * 180.f);
	if (currentgunSprite.getRotation() > 90 && currentgunSprite.getRotation() < 270)
	{
		currentgunSprite.setScale(1, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		angle += 0.02;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		angle -= 0.02;	
	}
}

sf::Sprite Crosshair::getSprite()
{
	return Sprite;
}
sf::Sprite Crosshair::getGunSprite()
{
	return currentgunSprite;
}
sf::Vector2f Crosshair::getPosition()
{
	return m_position;
}

