
#include "CollisionManager.h"



bool CollisionManager::CircleDetectCollision(sf::CircleShape &s1, sf::CircleShape &s2){

	//float distanceX = (s1.getPosition().x + s1.getRadius() / 2) - (s2.getPosition().x + s1.getRadius() / 2); // s1.getPosition().x - s2.getPosition().x;
	//float distanceY = (s1.getPosition().y + s1.getRadius() / 2) - (s2.getPosition().y + s1.getRadius() / 2);
	float distanceX =( s1.getPosition().x + s1.getRadius()) - (s2.getPosition().x + s2.getRadius());
	float distanceY = (s1.getPosition().y + s1.getRadius()) - (s2.getPosition().y + s2.getRadius());
	float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));
	if (distance < (s1.getRadius() +s2.getRadius())){
		return true;
		
	}
	else {
		return false;
	}
}
bool CollisionManager::CircleRectangleCollision(sf::CircleShape &s1, sf::RectangleShape &s2){
	if (s1.getGlobalBounds().intersects(s2.getGlobalBounds()))
	{

		return true;
	}
	else
	{
		return false;
	}
	

}

bool CollisionManager::RectangleRectangleCollision(sf::RectangleShape &s1, sf::RectangleShape &s2){
	if (s1.getGlobalBounds().intersects(s2.getGlobalBounds()))
	{

		return true;
	}
	else
	{
		return false;
	}


}

float CollisionManager::dotProduct(sf::Vector2f v1, sf::Vector2f v2){

	float answer((v1.x * v2.x) + (v1.y * v2.y));
	return answer;
}
sf::Vector2f CollisionManager::NormaliseVector(sf::Vector2f v1){

	float TempLength(sqrt((v1.x * v1.x) + (v1.y * v1.y)));
	sf::Vector2f normalised((v1.x / TempLength), (v1.y / TempLength));
	return normalised;

}



	

