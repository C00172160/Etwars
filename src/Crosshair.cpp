#include "Crosshair.h"

Crosshair::Crosshair()
{

}

Crosshair::Crosshair(sf::Texture& tex, sf::Vector2f pos)
{

	m_position = sf::Vector2f(pos.x + 30, pos.y + 30);
	//	m_position = sf::Vector2f(pos.x , pos.y );
	tex.setSmooth(true);
	Sprite.setTexture(tex);

}
void Crosshair::Init(sf::Texture& tex, sf::Vector2f pos)
{
	//m_position = sf::Vector2f(pos.x + 30, pos.y + 30);
	m_position = sf::Vector2f(pos.x, pos.y);
	tex.setSmooth(true);
	Sprite.setTexture(tex);
}

void Crosshair::Update(sf::Vector2f playerPos)
{

	//m_position = sf::Vector2f(playerPos.x + 30, playerPos.y - 35);
	//Sprite.setOrigin(10.f, 10.f);
	//Sprite.setPosition(m_position.x, m_position.y);

	//sf::Transform t;
	//t.rotate(angle, playerPos.x, playerPos.y);
	//sf::Rect<float> new_rect = t.transformRect(Sprite.getGlobalBounds());
	//Sprite.setPosition(new_rect.left + 10.f, new_rect.top + 10.f);
	//m_position = sf::Vector2f(new_rect.left + 10.f, new_rect.top + 10.f);

	sf::Vector2f playerPosition = sf::Vector2f(playerPos.x + 16, playerPos.y + 16);
	Sprite.setOrigin(10.f, 10.f);
	m_position = sf::Vector2f(playerPosition.x - 35, playerPosition.y - 35);
	Sprite.setPosition(m_position.x, m_position.y);

	float newx = cos(angle) *   (m_position.x - playerPosition.x) - sin(angle) * (m_position.y - playerPosition.y) + playerPosition.x;
	float newpy = sin(angle) * (m_position.x - playerPosition.x) + cos(angle) * (m_position.y - playerPosition.y) + playerPosition.y;

	m_position = sf::Vector2f(newx, newpy);
	Sprite.setPosition(m_position);







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
sf::Vector2f Crosshair::getPosition()
{

	return m_position;
}

