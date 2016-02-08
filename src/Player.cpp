#include "Player.h"

Player::Player()
{

}

Player::Player(int playerNumber, b2World& world, sf::Vector2f pos, sf::Texture &tex, int team, int type)
{
	m_position = pos;
	playerType = type;
	m_texture = tex;
	m_Alive = true;
	bodyalive = true;
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
	 bodyalive = obj.bodyalive;
	 numberOfFootContacts = obj.numberOfFootContacts;
	 isInair = obj.isInair;
	 timer = obj.timer;
	 move = obj.move;
	 m_Alive = obj.m_Alive;
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



void Player::Update(int numFootContacts, b2World & m_World)

{

	numberOfFootContacts = numFootContacts;
	if (bodyalive == true)
	{
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && numberOfFootContacts > 0) {
			m_body->ApplyForceToCenter(b2Vec2(0, -100), true);
		}

		if (m_body->GetLinearVelocity().y <= 0) {
			isInair = true;
		}
		else {
			isInair = false;
		}
		/*if (m_Alive == false && m_body->GetWorld()->IsLocked() == false && bodyalive == true)
		{
			m_position = sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
			bodyalive = false;
			m_body->GetWorld()->DestroyBody(m_body);
		}*/
	}
}
void Player::DestoryBody()
{
	if (m_Alive == false  && bodyalive == true)
		{
			m_position = sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
			bodyalive = false;
			m_body->GetWorld()->DestroyBody(m_body);
		}
}

void Player::UpdateSprite()
{
	
	
	healthtext = (std::to_string(health));
	Sprite.setPosition(m_body->GetPosition().x * SCALE  , m_body->GetPosition().y* SCALE );
	playerRectangle.setPosition(m_body->GetPosition().x * SCALE - 12, m_body->GetPosition().y* SCALE - 15);
	
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

bool Player::getAlive()
{
	return m_Alive;
}
void Player::setAlive(bool temp)
{
	m_Alive = temp;
}
bool Player::getBodyAlive()
{
	return bodyalive;
}
sf::Vector2f Player::getPosition()
{
	if (bodyalive == true)
	{
		return sf::Vector2f(m_body->GetPosition().x * SCALE, m_body->GetPosition().y * SCALE);
	}
	else
	{
		return m_position;
	}
}
	
sf::Vector2f Player::getVelocity()
{
	if (bodyalive == true)
	{
		return sf::Vector2f(m_body->GetLinearVelocity().x * SCALE, m_body->GetLinearVelocity().y * SCALE);
	}
	else
	{
		return sf::Vector2f(0, 0);
	}

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

