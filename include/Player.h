#ifndef PLAYER_H
#define PLAYER_H


#include <Box2D\Box2D.h>
#include "SFML/Graphics.hpp"


class Player {

public:
	Player();
	Player(b2World& world, sf::Vector2f pos, sf::Texture &tex, int id);
	void Update(int numFootContacts);
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	void setHealth(int damage);
	void UpdateSprite();
	int getHealth();


private:

	int health = 100;
	b2Body* m_body;
	int numberOfFootContacts;
	bool isInair;
	int timer = 0; 
	bool move = false;
	const float SCALE = 30.f;
	float playerHeight= 32;
	float playerWidth =32;
	sf::Vector2f source = sf::Vector2f(0, 0);
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::Sprite Sprite;
};

#endif



