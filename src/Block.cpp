#include "Block.h"

Block::Block(){
}
Block::Block(int c ,sf::Vector2f position,b2World& world){

	m_position = position;
	m_position = sf::Vector2f(position.x , position.y );
	type = c;
	createBlock(world, m_position,type);
	blockRectangle.setSize(sf::Vector2f(20, 20));
	blockCirlce.setRadius(10);
	blockCirlce.setOrigin(10, 10);

	blockCirlce.setPosition(m_position.x, m_position.y);
	blockCirlce.setFillColor(sf::Color::Transparent);
	blockCirlce.setOutlineThickness(0.5f);
	blockCirlce.setOutlineColor(sf::Color::Black);
}

	
	

void Block::createBlock(b2World& world, sf::Vector2f position,int type) {

	
	
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
	polygonShape2.SetAsBox(((20 / 2)) / SCALE, ((20 / 2)) / SCALE); //a 2x4 rectangle

	b2FixtureDef myFixtureDef2;

	myFixtureDef2.shape = &polygonShape2;
	myFixtureDef2.isSensor = true;
	SensorFixture = BlockBody->CreateFixture(&myFixtureDef2);
	SensorFixture->SetUserData("blocksensor");


	//if (type == 2){

	//	BlockBody->SetUserData("grass");
	//}
	//else if (type == 1){

	//	BlockBody->SetUserData("dirt");

	//}

	if (type == 8){

		BlockBody->SetUserData("dirt");
		lives = 1;
	}
    else if (type == 6){

		BlockBody->SetUserData("topStraight");
		lives = 1;

	}
	else if (type == 9){

		BlockBody->SetUserData("leftStraight");
		lives = 1;

	}
	else if (type == 7){

		BlockBody->SetUserData("topLeftCorner");
		lives = 1;

	}
	else if (type == 4){

		BlockBody->SetUserData("topRightCorner");
		lives = 1;

	}
	else if (type == 5){

		BlockBody->SetUserData("rightStraight");
		lives = 1;

	}
	else if (type == 2){

		BlockBody->SetUserData("bottomStraight");
		lives = 1;

	}
	else if (type == 3){

		BlockBody->SetUserData("bottomRightCorner");
		lives = 1;

	}
	else if (type == 1){

		BlockBody->SetUserData("bottomLeftCorner");
		lives = 1;

	}
	else if (type == 10){

		BlockBody->SetUserData("concrete");
		lives = 3;

	}
	else if (type == 11){

		BlockBody->SetUserData("steel");
		lives = 5;

	}
	blockRectangle.setOrigin(10, 10);
	blockRectangle.setPosition(BlockBody->GetPosition().x*SCALE, BlockBody->GetPosition().y*SCALE);

}

void Block::CheckLives()
{
		lives -= 1;

		if (lives <= 0)
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
sf::RectangleShape& Block::getRect()
{
	return blockRectangle;
}
sf::CircleShape& Block::getCircle()
{
	return blockCirlce;
}