#ifndef PLAYER_H
#define PLAYER_H


#include <Box2D\Box2D.h>
#include "SFML/Graphics.hpp"
#include "game.hpp"

class Player {

public:
	Player();
	Player(b2World& world, sf::Vector2f pos, sf::Texture &tex, int team,int type);
	void Update(int numFootContacts);
	sf::Sprite getSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	

	void setHealth(int damage);
	void UpdateSprite();
	int getHealth();
	void Init(int playerNumber, b2World& world, sf::Vector2f pos, sf::Texture &tex, int team, int type);
	int getID();
	int getRocketSensor();
	std::string getHealthText();
	int getType();
	sf::RectangleShape getPlayerRectangle();
	


private:
	sf::RectangleShape playerRectangle;
	int playernum;
	int health ;
	b2Body* m_body;
	int numberOfFootContacts;
	bool isInair;
	int timer = 0; 
	bool move = false;
	const float SCALE = 30.f;
	float playerHeight= 30;
	float playerWidth =24;
	sf::Vector2f source = sf::Vector2f(0, 0);
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Vector2f m_velocity;
	sf::Sprite Sprite;
	void* RocketSensor;
	sf::Font font;
	std::string healthtext;
	int playerType;

};

#endif



