#include "Rocket.h"


Rocket::~Rocket()
{


}
Rocket::Rocket()
{

}
Rocket::Rocket(b2World& world, sf::Vector2f pos, sf::Texture &tex, sf::Vector2f PlayerPos,float power)
{
	
//	m_position = pos +sf::Vector2f(10.5,5);
	m_position = pos;
	m_texture = tex;

	collisioncircle.setFillColor(sf::Color::Black);
	collisioncircle.setOrigin(16, 16);
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = false;
	myBodyDef.position = b2Vec2(m_position.x / SCALE, m_position.y / SCALE);

	m_body = world.CreateBody(&myBodyDef);

	b2CircleShape Shape;
	//Shape.SetAsBox((Width/ 2) / SCALE, (Height / 2) / SCALE);
	Shape.m_radius = 15/SCALE;
	b2FixtureDef FixtureDef;
	
	FixtureDef.density = 0.1f;
	FixtureDef.friction = 1.f;
	FixtureDef.shape = &Shape;
	m_body->CreateFixture(&FixtureDef);
	m_body->SetUserData("rocket");
	
	collisioncircle.setRadius(16);
	//add  sensor fixture
	b2PolygonShape polygonShape2;
	//polygonShape2.SetAsBox((Width / SCALE) + 0.3f, (Height / SCALE) + 0.3f); //a 2x4 rectangle
	polygonShape2.SetAsBox((Width / 2) / SCALE, (Height / 2) / SCALE);
	b2FixtureDef myFixtureDef2;

	myFixtureDef2.shape = &polygonShape2;
	myFixtureDef2.isSensor = true;
    SensorFixture = m_body->CreateFixture(&myFixtureDef2);
	SensorFixture->SetUserData("rocketsensor");

	tex.setSmooth(true);
	Sprite.setTexture(tex);
	Sprite.setOrigin(15 , 15 );
	//Sprite.setOrigin(0,0);

	sf::Vector2f Direction = pos - (sf::Vector2f(PlayerPos.x,PlayerPos.y));
	float length = sqrt((Direction.x * Direction.x) + (Direction.y * Direction.y));
	Direction = Direction / length;
	float Power = power;

	m_body->ApplyForceToCenter(b2Vec2((Direction.x*Power)/SCALE,(Direction.y * Power)/SCALE), true);

}
void Rocket::Update(b2World& world)
{
	Sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y* SCALE);
	Sprite.setRotation(m_body->GetAngle() * 180 / b2_pi);
	collisioncircle.setPosition((m_body->GetPosition().x * SCALE), (m_body->GetPosition().y* SCALE));
	angle = atan2((double)m_body->GetLinearVelocity().y, (double)m_body->GetLinearVelocity().x);
	m_body->SetTransform(m_body->GetWorldCenter(), angle - ((float)M_1_PI) / 2.0f);
}

sf::Sprite Rocket::getSprite()
{

	return Sprite;
}


b2Body* Rocket::getBody()
{

	return m_body;
}
sf::Vector2f Rocket::getPosition()
{

	return sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
}
sf::Vector2f Rocket::getVelocity()
{

	return sf::Vector2f(m_body->GetLinearVelocity().x * SCALE, m_body->GetLinearVelocity().y * SCALE);
}
void Rocket::setAlive(bool boolean)
{

	alive = boolean;
}
sf::CircleShape Rocket::getCircle()
{

	return collisioncircle;
}
