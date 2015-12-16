#include "Player.h"

Player::Player()
{

}

Player::Player(b2World& world, sf::Vector2f pos, sf::Texture &tex, int id)
{
	//
	//m_position = pos;
	//m_texture = tex;

	//

	//b2BodyDef myBodyDef;
	//myBodyDef.type = b2_dynamicBody;
	//myBodyDef.fixedRotation = true;
	//myBodyDef.position = b2Vec2(m_position.x / SCALE, m_position.y / SCALE);

	//m_body = world.CreateBody(&myBodyDef);

	//b2PolygonShape Shape;
	//Shape.SetAsBox((playerWidth / 2) / SCALE, (playerHeight / 2) / SCALE);
	//b2FixtureDef FixtureDef;
	//FixtureDef.density = 1.f;
	//FixtureDef.friction = 0.7f;
	//FixtureDef.shape = &Shape;

	//m_body->CreateFixture(&FixtureDef);
	//

	////add foot sensor fixture
	//b2PolygonShape polygonShape2;
	//polygonShape2.SetAsBox((30.f / 2) / SCALE, (40.f / 2) / SCALE); //a 2x4 rectangle

	//b2FixtureDef myFixtureDef2;

	//myFixtureDef2.shape = &polygonShape2;
	//myFixtureDef2.isSensor = true;
	//b2Fixture* footSensorFixture = m_body->CreateFixture(&myFixtureDef2);
	//if (id ==1)
	//{
	//	footSensorFixture->SetUserData("player1");
	//}
	//else if (id == 2)
	//{
	//	footSensorFixture->SetUserData("player2");
	//}
	//


	//tex.setSmooth(true);
	//Sprite.setTexture(tex);
	////Sprite.setOrigin(16.f, 16.f);
	//Sprite.setOrigin(0, 0);
	//Sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));

	  
}
void Player::Init(b2World& world, sf::Vector2f pos, sf::Texture &tex, int id)
{
	m_position = pos;
	m_texture = tex;

	health = 100;

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = true;
	myBodyDef.position = b2Vec2(m_position.x / SCALE, m_position.y / SCALE);

	m_body = world.CreateBody(&myBodyDef);

	b2Vec2 vertices[6];
	vertices[0].Set(-0.4, -0.5);
	vertices[1].Set(0.4, -0.5);
	vertices[2].Set(0.4, 0.3);
	vertices[3].Set(0.2, 0.5);
	vertices[4].Set(-0.2,0.5 );
	vertices[5].Set(-0.4, 0.3);

	b2PolygonShape Shape;
	Shape.Set(vertices, 6); //pass array to the shape
	//b2PolygonShape Shape;
	//Shape.SetAsBox((12) / SCALE, (15) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;
	m_body->CreateFixture(&FixtureDef);


	b2PolygonShape polygonShape3;
	polygonShape3.SetAsBox(((12.f / 2) / SCALE), ((15.f / 2) / SCALE)); //a 2x4 rectangle

	b2FixtureDef myFixtureDef3;

	myFixtureDef3.shape = &polygonShape3;
	myFixtureDef3.isSensor = true;
	b2Fixture* RocketSensorFixture = m_body->CreateFixture(&myFixtureDef3);
	if (id == 1)
	{
		RocketSensorFixture->SetUserData("player1Sensor");
	}
	else if (id == 2)
	{
		RocketSensorFixture->SetUserData("player2Sensor");
	}

	//add foot sensor fixture
	b2PolygonShape polygonShape2;
	polygonShape2.SetAsBox(((15.f / 2)  / SCALE), ((32.f / 2) / SCALE)); //a 2x4 rectangle

	b2FixtureDef myFixtureDef2;

	myFixtureDef2.shape = &polygonShape2;
	myFixtureDef2.isSensor = true;
	b2Fixture* footSensorFixture = m_body->CreateFixture(&myFixtureDef2);
	if (id == 1)
	{
		footSensorFixture->SetUserData("player1");
	}
	else if (id == 2)
	{
		footSensorFixture->SetUserData("player2");
	}



	tex.setSmooth(true);
	Sprite.setTexture(tex);
	Sprite.setOrigin(12.f, 15.f);
	//Sprite.setOrigin(0, 0);
	Sprite.setTextureRect(sf::IntRect(source.x * 24, source.y * 30, 24, 30));
}
void Player::Update(int numFootContacts)

{
	numberOfFootContacts = numFootContacts;

	


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move = true;
		m_body->ApplyForceToCenter(b2Vec2(10, 0), true);

		source.y = 0;


	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move = true;

		m_body->ApplyForceToCenter(b2Vec2(-10, 0), true);

		source.y = 1;

	}
	else
		move = false;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && numberOfFootContacts >0) {


		m_body->ApplyForceToCenter(b2Vec2(0,- 100), true);
	}


	if (m_body->GetLinearVelocity().y <= 0) {
		isInair = true;
	}
	else {
		isInair = false;
	}


	


}
void Player::UpdateSprite()
{
	
	Sprite.setPosition(m_body->GetPosition().x * SCALE  , m_body->GetPosition().y* SCALE );
	//Sprite.setRotation(m_body->GetAngle() * 180 / b2_pi);


	timer++;
	if (timer >= 5)
	{
		source.x++;
		if (source.x > 5){

			source.x = 0;
		}
		timer = 0;
	}

	if (move == true)
	{
		Sprite.setTextureRect(sf::IntRect(source.x * 24, source.y * 30, 24, 30));
	}



}

sf::Sprite Player::getSprite()
{

	return Sprite;
}
sf::Vector2f Player::getPosition()
{

	return sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
}
sf::Vector2f Player::getVelocity()
{
	return sf::Vector2f(m_body->GetLinearVelocity().x * SCALE, m_body->GetLinearVelocity().y * SCALE);
}

void Player::setHealth(int damage)
{
	health = health - damage;

}
int Player::getHealth()
{
	return health;

}