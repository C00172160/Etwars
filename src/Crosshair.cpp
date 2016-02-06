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
}

void Crosshair::Update(sf::Vector2f playerPos, int guntype, Player& player)
{
	gunPosition = playerPos;
	sf::Vector2f playerPosition = sf::Vector2f(playerPos.x  , playerPos.y  );
	Sprite.setOrigin(10.f, 10.f);
	m_position = sf::Vector2f(playerPosition.x +gunoffset , playerPosition.y );

	Sprite.setPosition(m_position.x, m_position.y);

	float newx = cos(angle) *   (m_position.x - playerPosition.x) - sin(angle) * (m_position.y - playerPosition.y) + playerPosition.x;
	float newpy = sin(angle) * (m_position.x - playerPosition.x) + cos(angle) * (m_position.y - playerPosition.y) + playerPosition.y;

	m_position = sf::Vector2f(newx, newpy);
	Sprite.setPosition(m_position);

	if (guntype == 1)
	{
		currentgunSprite = rocketLauncher;
		gunoffset = 60;
	}
	else if (guntype == 2)
	{
		currentgunSprite = handgun;
		gunoffset = 60;
	}
	else if (guntype == 3)
	{
		currentgunSprite = shotgun;
		gunoffset = 60;
	}
	else if (guntype == 4)
	{
		currentgunSprite = sniper;
		gunoffset = 120;
	}

	
	/*\begin{align}
x'&=x\cos\theta-y\sin\theta\\
y'&=x\sin\theta+y\cos\theta.
        \end{align}*/
	currentgunSprite.setOrigin(currentgunSprite.getGlobalBounds().width / 2, currentgunSprite.getGlobalBounds().height / 2);
	currentgunSprite.setPosition(playerPos);
	currentgunSprite.setRotation(angle/M_PI * 180.f);
	
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

