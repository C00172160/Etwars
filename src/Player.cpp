#include "Player.h"

Player::Player()
{

}

Player::Player(int playerNumber, b2World& world, sf::Vector2f pos, sf::Texture &tex, int team, int type)
{
	m_position = pos;
	playerType = type;
	m_texture = tex;
	
	if (team == 1)
	{
		playernum = playerNumber;
	}
	else if (team == 2)
	{
		playernum = playerNumber * 100;
	}
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
	vertices[4].Set(-0.2, 0.5);
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

	if (team == 1)
	{
		//std::string RocketSensorstring = "Player1" + std::to_string(playernum);
		//RocketSensor = static_cast<void*>(&RocketSensorstring);
		RocketSensorFixture->SetUserData((void*)(playernum * 1000));
	}
	else if (team == 2)
	{
		std::string RocketSensorstring = "Player2" + std::to_string(playernum);
		RocketSensor = static_cast<void*>(&RocketSensorstring);
		RocketSensorFixture->SetUserData((void*)(playernum * 1000));
	}
	else if (team == 4)
	{
		RocketSensorFixture->SetUserData("captain2sensor");
	}
	else if (team == 3)
	{
		RocketSensorFixture->SetUserData("captain1sensor");
	}

	//add foot sensor fixture
	b2PolygonShape polygonShape2;
	polygonShape2.SetAsBox(((15.f / 2) / SCALE), ((32.f / 2) / SCALE)); //a 2x4 rectangle
	b2FixtureDef myFixtureDef2;

	myFixtureDef2.shape = &polygonShape2;
	myFixtureDef2.isSensor = true;

	b2Fixture * footSensorFixture = m_body->CreateFixture(&myFixtureDef2);
	/*if (team == 1)
	{
	footSensorFixture->SetUserData("player1foot");
	}
	else if (team == 2)
	{
	footSensorFixture->SetUserData("player2foot");
	}*/
	footSensorFixture->SetUserData((void*)playernum);


	tex.setSmooth(true);
	Sprite.setTexture(tex);
	Sprite.setOrigin(12.f, 15.f);
	//Sprite.setOrigin(0, 0);
	Sprite.setTextureRect(sf::IntRect(source.x * 24, source.y * 30, 24, 30));
	playerRectangle.setSize(sf::Vector2f(24, 30));
	playerRectangle.setPosition(m_body->GetPosition().x * SCALE - 12, m_body->GetPosition().y* SCALE - 15);
	playerRectangle.setFillColor(sf::Color::Black);

}
Player::Player(const Player &obj)
{
     playerRectangle = obj.playerRectangle;
	 playernum = obj.playernum;
	 health = obj.health;
	 m_body = obj.m_body;

	 numberOfFootContacts = obj.numberOfFootContacts;
	 isInair = obj.isInair;
	 timer = obj.timer;
	 move = obj.move;
	 SCALE = obj.SCALE;
	 playerHeight = obj.playerHeight;
	 playerWidth = obj.playerWidth;
	source = obj.source;
	 m_position = obj.m_position;
	 m_texture = obj.m_texture;
	 m_velocity = obj.m_velocity;
	 Sprite = obj.Sprite;
	 RocketSensor = obj.RocketSensor;
	 font = obj.font;
	 healthtext = obj.healthtext;
	 playerType = obj.playerType;
}
//void Player::Init(int playerNumber, b2World& world, sf::Vector2f pos, sf::Texture &tex, int team, int type)
//{
//	
//	//if (team == 1)
//	//{
//	//	playernum = playerNumber;
//	//}
//	//else if (team == 2)
//	//{
//	//	playernum = playerNumber * 100;
//	//}
//	//health = 100;
//	//b2BodyDef myBodyDef;
//	//myBodyDef.type = b2_dynamicBody;
//	//myBodyDef.fixedRotation = true;
//	//myBodyDef.position = b2Vec2(m_position.x / SCALE, m_position.y / SCALE);
//
//	//m_body = world.CreateBody(&myBodyDef);
//
//	//b2Vec2 vertices[6];
//	//vertices[0].Set(-0.4, -0.5);
//	//vertices[1].Set(0.4, -0.5);
//	//vertices[2].Set(0.4, 0.3);
//	//vertices[3].Set(0.2, 0.5);
//	//vertices[4].Set(-0.2,0.5 );
//	//vertices[5].Set(-0.4, 0.3);
//
//	//b2PolygonShape Shape;
//	//Shape.Set(vertices, 6); //pass array to the shape
//	////b2PolygonShape Shape;
//	////Shape.SetAsBox((12) / SCALE, (15) / SCALE);
//	//b2FixtureDef FixtureDef;
//	//FixtureDef.density = 1.f;
//	//FixtureDef.friction = 0.7f;
//	//FixtureDef.shape = &Shape;
//	//m_body->CreateFixture(&FixtureDef);
//
//
//	//b2PolygonShape polygonShape3;
//	//polygonShape3.SetAsBox(((12.f / 2) / SCALE), ((15.f / 2) / SCALE)); //a 2x4 rectangle
//
//	//b2FixtureDef myFixtureDef3;
//
//	//myFixtureDef3.shape = &polygonShape3;
//	//myFixtureDef3.isSensor = true;
//	//b2Fixture* RocketSensorFixture = m_body->CreateFixture(&myFixtureDef3);
//
//	//if (team == 1)
//	//{
//	//	//std::string RocketSensorstring = "Player1" + std::to_string(playernum);
//	//	//RocketSensor = static_cast<void*>(&RocketSensorstring);
//	//	RocketSensorFixture->SetUserData((void*)(playernum*1000));
//	//}
//	//else if (team == 2)
//	//{
//	//	std::string RocketSensorstring = "Player2" + std::to_string(playernum);
//	//	RocketSensor = static_cast<void*>(&RocketSensorstring);
//	//	RocketSensorFixture->SetUserData((void*)(playernum * 1000));
//	//}
//	//else if (team == 4)
//	//{
//	//	RocketSensorFixture->SetUserData("captain2sensor");
//	//}
//	//else if (team == 3)
//	//{
//	//	RocketSensorFixture->SetUserData("captain1sensor");
//	//}
//
//	////add foot sensor fixture
//	//b2PolygonShape polygonShape2;
//	//polygonShape2.SetAsBox(((15.f / 2)  / SCALE), ((32.f / 2) / SCALE)); //a 2x4 rectangle
//	//b2FixtureDef myFixtureDef2;
//
//	//myFixtureDef2.shape = &polygonShape2;
//	//myFixtureDef2.isSensor = true;
//	//
//	//b2Fixture * footSensorFixture = m_body->CreateFixture(&myFixtureDef2);
//	///*if (team == 1)
//	//{
//	//	footSensorFixture->SetUserData("player1foot");
//	//}
//	//else if (team == 2)
//	//{
//	//	footSensorFixture->SetUserData("player2foot");
//	//}*/
//	//footSensorFixture->SetUserData((void*)playernum);
//	//
//
//	//tex.setSmooth(true);
//	//Sprite.setTexture(tex);
//	//Sprite.setOrigin(12.f, 15.f);
//	////Sprite.setOrigin(0, 0);
//	//Sprite.setTextureRect(sf::IntRect(source.x * 24, source.y * 30, 24, 30));
//	//playerRectangle.setSize(sf::Vector2f(24, 30));
//	//playerRectangle.setPosition(m_body->GetPosition().x * SCALE - 12, m_body->GetPosition().y* SCALE - 15);
//	//playerRectangle.setFillColor(sf::Color::Black);
//   
//}


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
	
	//healthtext.setPosition((m_body->GetPosition().x * SCALE) - 10, (m_body->GetPosition().y * SCALE) - 40);
	healthtext = (std::to_string(health));
	Sprite.setPosition(m_body->GetPosition().x * SCALE  , m_body->GetPosition().y* SCALE );
	playerRectangle.setPosition(m_body->GetPosition().x * SCALE - 12, m_body->GetPosition().y* SCALE - 15);
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
sf::RectangleShape& Player::getPlayerRectangle(){
	return playerRectangle;
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
int  Player::getID()
{
	return playernum;
}

int Player::getRocketSensor()
{
	return playernum * 1000;
}
std::string Player::getHealthText()
{
	
	return healthtext;
}
int Player::getType(){

	return playerType;
}
b2Body* Player::getBody()
{
	return m_body;
}

