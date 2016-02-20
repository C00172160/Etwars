#ifndef ROCKET_H
#define ROCKET_H
#define _USE_MATH_DEFINES

#include <Box2D\Box2D.h>
#include "SFML/Graphics.hpp"
#include <math.h>

#include <SFML/Graphics.hpp>
#include "game_state.hpp"




class Rocket{

	public:
		Rocket();
		~Rocket();
		Rocket(b2World& world, sf::Vector2f pos, sf::Texture &tex, sf::Vector2f PlayerPos,float power);
		sf::Sprite getSprite();
		void Update(b2World& world);
		sf::Vector2f getPosition();
		b2Body* Rocket::getBody();
		void setAlive(bool boolean);
		sf::Vector2f getVelocity();
		sf::CircleShape getCircle();

	



	private:
		bool alive = true;
		b2Body* m_body;
		float Height = 30;
		float Width = 30;
		const float SCALE = 30.f;
		sf::Vector2f m_position;
		sf::Texture m_texture;
		sf::Vector2f m_velocity;
		sf::Sprite Sprite;
		float angle;
		b2Fixture* SensorFixture;
		sf::CircleShape collisioncircle;

};



#endif