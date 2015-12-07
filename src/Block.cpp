#include "Block.h"

Block::Block(){
}
Block::Block(char c ,sf::Vector2f position,b2World& world){

	m_position = position;
	m_position = sf::Vector2f(position.x * 20, position.y * 20);
	type = c;
	createBlock(world, m_position);
	circle.setOrigin(10, 10);
	circle.setRadius(10);
	circle.setPosition(m_position.x , m_position.y );
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(5.f);
	circle.setOutlineColor(sf::Color::Black);
}

	
	

void Block::createBlock(b2World& world, sf::Vector2f position) {

	
	
	const float SCALE = 30.f;

	
	b2BodyDef blockDef;
	//blockDef.position = b2Vec2(position.x/SCALE,position.y/SCALE);
	blockDef.position = b2Vec2(position.x/SCALE , position .y /SCALE);
	blockDef.type = b2_staticBody;
    BlockBody = world.CreateBody(&blockDef);

	b2PolygonShape blockShape;
	blockShape.SetAsBox((10) / SCALE , (10 ) / SCALE );
	b2FixtureDef blockFixture;
	blockFixture.density = 0.5f;
	blockFixture.shape = &blockShape;
	BlockBody->CreateFixture(&blockFixture);
//	BlockBody->SetUserData((void*)1);



	b2PolygonShape polygonShape2;
	polygonShape2.SetAsBox(((20 / 2) + 2.f) / SCALE, ((20 / 2) + 2.f) / SCALE); //a 2x4 rectangle

	b2FixtureDef myFixtureDef2;

	myFixtureDef2.shape = &polygonShape2;
	myFixtureDef2.isSensor = true;
	SensorFixture = BlockBody->CreateFixture(&myFixtureDef2);
	SensorFixture->SetUserData("blocksensor");


	if (GrassSymbols.find(type)){

		BlockBody->SetUserData("grass");
	}
	else if (DirtSymbols.find(type)){

		BlockBody->SetUserData("dirt");

	}


}

void Block::Update(sf::CircleShape& circle2)
{
	/*if (m_position.x   > rect.getPosition().x  &&
		m_position.x  < (rect.getPosition().x  + rect.getSize().x ) &&
		m_position.y  > rect.getPosition().y  &&
		m_position.y  < (rect.getPosition().y  + rect.getSize().y))
	{
		alive = false;
	}*/
	if (CollisionManager::CircleDetectCollision(circle, circle2) == true)
	{
		alive = false;
	}

}
bool Block::getAlive()
{
	return alive;

}
b2Body* Block::getBody()
{

	return BlockBody;
	
}
sf::CircleShape& Block::getCircle(){

	return circle;
}