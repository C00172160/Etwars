#include "Player.h"

Player::Player(b2World& world, sf::Vector2f pos, sf::Texture &tex, int id)
{
	
	m_position = pos;
	m_texture = tex;

	

	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.fixedRotation = true;
	myBodyDef.position = b2Vec2(m_position.x / SCALE, m_position.y / SCALE);

	m_body = world.CreateBody(&myBodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((playerWidth / 2) / SCALE, (playerHeight / 2) / SCALE);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.7f;
	FixtureDef.shape = &Shape;

	m_body->CreateFixture(&FixtureDef);
	

	//add foot sensor fixture
	b2PolygonShape polygonShape2;
	polygonShape2.SetAsBox((30.f / 2) / SCALE, (40.f / 2) / SCALE); //a 2x4 rectangle

	b2FixtureDef myFixtureDef2;

	myFixtureDef2.shape = &polygonShape2;
	myFixtureDef2.isSensor = true;
	b2Fixture* footSensorFixture = m_body->CreateFixture(&myFixtureDef2);
	if (id ==1)
	{
		footSensorFixture->SetUserData("player1");
	}
	else if (id == 2)
	{
		footSensorFixture->SetUserData("player2");
	}
	


	tex.setSmooth(true);
	Sprite.setTexture(tex);
	Sprite.setOrigin(16.f, 16.f);

	Sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));

	  
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


		m_body->ApplyForceToCenter(b2Vec2(0,- 50), true);
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
	Sprite.setPosition(m_body->GetPosition().x * SCALE, m_body->GetPosition().y* SCALE);
	Sprite.setRotation(m_body->GetAngle() * 180 / b2_pi);


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
		Sprite.setTextureRect(sf::IntRect(source.x * 32, source.y * 32, 32, 32));
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

void Player::setHealth(int damage)
{
	health = health - damage;

}
int Player::getHealth()
{
	return health;

}