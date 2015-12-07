


#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include <time.h> 
#include "SFML/OpenGL.hpp" 


#include <iostream> 
#include <array>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <vector>
#include "Block.h"
#include "zlib.h"
#include <Box2D\Box2D.h>
#include "Player.h"
#include "tmx\MapLoader.h"
#include "Crosshair.h"
#include "Rocket.h"


using namespace std;

/** We need this to easily convert between pixel and real-world coordinates*/
static const float SCALE = 30.f;

/** Create the base for the boxes to land */
void CreateGround(b2World& World, float X, float Y);
void DestroyDeadbodies();
/** Create the boxes */
void CreateBox(b2World& World, int MouseX, int MouseY);
void createBlock(b2World& world, sf::Vector2f position);

//global scope
int numFootContacts;
int numFootContacts2;
bool player1hit = false;
bool player2hit = false;
bool Groundhit = false;
b2Vec2 Gravity(0.f, 10.0f);
b2World World(Gravity);
sf::Vector2f lastbulletpos;
bool destroyRocket = false;




class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {
		//check if fixture A was the foot sensor
		void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
		void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

		
		if (fixtureUserDataA == "rocketsensor" || fixtureUserDataB == "rocketsensor")//if A ROCKET HITS ANYTHING
		{
			destroyRocket = true;
		}

		 if (fixtureUserDataA == "player1"  || fixtureUserDataB == "player1")
		{
			numFootContacts++;
		}
		 if (fixtureUserDataA == "player2" || fixtureUserDataB == "player2")
		{
			numFootContacts2++;
		}

	}

	void EndContact(b2Contact* contact) {

		void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
		void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();

		//if ((int)fixtureUserDataA == 3 && ((int)fixtureUserDataB == 1 || (int)fixtureUserDataB == 2))
		//{
		//	numFootContacts--;
		//}

		if (fixtureUserDataA == "player1" || fixtureUserDataB == "player1")
		{
			numFootContacts--;
		}
		 if (fixtureUserDataA == "player2" || fixtureUserDataB == "player2")
		{
			numFootContacts2--;
		}

		 if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "player1") ||
			(fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "player1"))//if A ROCKET HITS Player1
		{
			destroyRocket = true;
			player1hit = true;
			
		
		}
		  if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "player2") ||
			(fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "player2"))//if A ROCKET HITS Player2
		{
			destroyRocket = true;
			player2hit = true;
		}
		  if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "blocksensor") ||
			      (fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "blocksensor" ))//if A ROCKET HITS ground
		 {
			 Groundhit = true;
			 destroyRocket = true;
			
		 }
	}
};


MyContactListener myContactListenerInstance;

int main()
{
	sf::String blockSymbols = "01";
	sf::String DirtSymbols = "1";
	sf::Vector2f position(400, 50);
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
	Window.setFramerateLimit(60);
	int wormcount = 0;
	/** Prepare the world */
	bool Player1Turn = true;
	sf::Text player1health;
	player1health.setFont(font);
	
	player1health.setStyle(sf::Text::Bold);
	player1health.setPosition(0, 0);
	player1health.setCharacterSize(20);
	player1health.setColor(sf::Color::Black);

	sf::Text player2health;
	player2health.setFont(font);

	player2health.setStyle(sf::Text::Bold);
	player2health.setPosition(0, 0);
	player2health.setCharacterSize(20);
	player2health.setColor(sf::Color::Black);

	vector<Block> blocks;

	sf::String map[] = {    "00000000000000000000000000000000000000000000",
							"00000000000000000000000000000000000000000000",
							"00000000000000000000000000000000000000000000",
							"00000000000000000000000000000000000000000000",
							"00000000000000000000010000000000000000000000",
							"00000000000000000000000000000000000000000000",
							"00000000000000000000000000000000000000000000",
							"00000000000000000000000000000000000000000000",
							"00000000000000000000000000000000000000000000",
							"22222222222222222222200022222222222222222222",
							"11111111111111111111100011111111111111111111",
							"11111111111111111111100011111111111111111111",
							"11111111111111111110000011111111111111111111",
							"11111111111111111100000111111111111111111111",
							"11111111111111110000011111111111111111111111",
							"11111111111111000000111111111111111111111111",
							"11111111111110000001111111111111111111111111",
							"11111111111110000001111100111111111111111111",
							"11111111111110000001111000011111111111111111",
							"10000000000000000000000000000001100000000001",
							"11000000000000000000000000000000000000000011",
							"00000000000000000000000000000000000000000000",
							"00000000000000000000000000000000011000000000",
							"11111111111111111111111100000111111111111111",
							"11111111111111111111111100000111111111111111",
							"11111111111111111111111111111111111111111111",
							"11111111111111111111111111111111111111111111",
							"11111111111111111111111111111111111111111111",
							"11111111111111111111111111111111111111111111",
							"11111111111111111111111111111111111111111111"};
					


	
	sf::Texture grasstexture;
	sf::Texture backGroundTexture;
	sf::Texture CharacterTexture;
	sf::Texture DirtTexture;
	sf::Texture CrosshairTexture;
	sf::Texture RocketTexture;

	int sizeofmap = 0;
	RocketTexture.loadFromFile("Resources/Rocket.png");
	CrosshairTexture.loadFromFile("Resources/crosshair.png");
	backGroundTexture.loadFromFile("Resources/background.jpg");
	DirtTexture.loadFromFile("Resources/dirt1.png");
	grasstexture.loadFromFile("Resources/grass1.png");
	CharacterTexture.loadFromFile("Resources/weird.png");
	numFootContacts = 0;
	Player player1(World, position, CharacterTexture,1);
	Player player2(World, position + sf::Vector2f(100,0), CharacterTexture,2);

	Crosshair cross(CrosshairTexture,position);
	bool player1Fire = false , player2Fire = false;
	std::vector<Rocket> Rockets;
	sf::Sprite background;
	background.setTexture(backGroundTexture);
	background.setPosition(sf::Vector2f(0, 00));

	World.SetContactListener(&myContactListenerInstance);
	sf::CircleShape boundingbox(50);
	boundingbox.setPosition(-500, -500);
	boundingbox.setFillColor(sf::Color::Transparent);
	boundingbox.setOutlineThickness(5.f);
	boundingbox.setOutlineColor(sf::Color::Black);




	int h = 30;
	int w = 44;

	for (int y = 0; y < h; y++) {

		for (int x = 0; x < w; x++) {

			char c = map[y][x];

				if (blockSymbols.find(c)) {
					Block temp = Block(map[y][x], sf::Vector2f(x, y), World);
					blocks.push_back(temp);
				}
			

		}
	}


	while (Window.isOpen())
	{


		World.Step(1 / 60.f, 8, 3);

		Window.clear(sf::Color::White);

		Window.draw(background);
		int BodyCount = 0;

		for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
		{
			if (BodyIterator->GetType() == b2_staticBody){

				if (BodyIterator->GetUserData() == "dirt"){
					sf::Sprite DirtSprite;
					DirtSprite.setTexture(DirtTexture);
					DirtSprite.setOrigin(10, 10);
					DirtSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
					DirtSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
					Window.draw(DirtSprite);
					++BodyCount;
				}
				else if (BodyIterator->GetUserData() == "grass"){
					sf::Sprite grassSprite;
					grassSprite.setTexture(grasstexture);
					grassSprite.setOrigin(10, 10);
					grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
					grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
					Window.draw(grassSprite);
					++BodyCount;
				}

			}


		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if (Rockets.size() < 1)
			{
				if (Player1Turn == true)
				{
					player1Fire = true;
					Rocket tempRocket(World, cross.getPosition(), RocketTexture, player1.getPosition());
					Rockets.push_back(tempRocket);
				}
				else
				{
					player2Fire = true;
					Rocket tempRocket(World, cross.getPosition(), RocketTexture, player2.getPosition());
					Rockets.push_back(tempRocket);
				}
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			Player1Turn = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			Player1Turn = true;
		}
	
		

		if (Player1Turn == true)
		{
			cross.Update(player1.getPosition());
			player1.Update(numFootContacts);

		}
		else
		{
		cross.Update(player2.getPosition());
		player2.Update(numFootContacts2);
		}


		if (player1hit == true)
		{
			player1.setHealth(20);
			player1hit = false;
		}
		if (player2hit == true)
		{
			player2.setHealth(20);
			player2hit = false;
		}

		if (destroyRocket == true && World.IsLocked() == false)
		{
			for (int i = 0; i < Rockets.size(); i++)
			{
				lastbulletpos = Rockets[i].getPosition();
				World.DestroyBody(Rockets[i].getBody());
				Rockets.pop_back();
				destroyRocket = false;

				if (Player1Turn == true)
				{
					player1Fire = false;
					Player1Turn = false;
				}
				else if (Player1Turn == false)
				{
					player2Fire = false;
					Player1Turn = true;
				}
			}
		}
		
	
		World.DrawDebugData();
		player1.UpdateSprite();
		player2.UpdateSprite();
	
		sf::View player1View,player2View, bulletView;
	    
		player1View.setCenter(sf::Vector2f(player1.getPosition()));// , sf::Vector2f(500, 500));#

		for (int i = 0; i < Rockets.size(); i++)
		{
			bulletView.setCenter(sf::Vector2f(Rockets[i].getPosition()));
		}

		player1View.setSize(500, 500);
		player2View.setCenter(sf::Vector2f(player2.getPosition()));
		player2View.setSize(500, 500);
		
		if (Player1Turn == true)
		{
			Window.setView(player1View);
			for (int i = 0; i < Rockets.size(); i++)
			{
				if (player1Fire == true)
				{
					Window.setView(bulletView);
				}
			}
		}
		else if (Player1Turn == false)
		{
			Window.setView(player2View);
			for (int i = 0; i < Rockets.size(); i++)
			{
				if (player2Fire == true)
				{
					Window.setView(bulletView);
				}
			}
		}
	
		
	

		//player1View.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));

		
		Window.draw(player1.getSprite());
		Window.draw(player2.getSprite());
		Window.draw(cross.getSprite());



		for (int i = 0; i < Rockets.size(); i++)
		{

			Rockets[i].Update(World);
			if (Rockets[i].getPosition().x + 22 < 0 || Rockets[i].getPosition().x -22 > 800 || Rockets[i].getPosition().y > 600)
			{
				destroyRocket = true;


			}


			Window.draw(Rockets[i].getSprite());
		}
		player1health.setPosition(player1.getPosition().x-10, player1.getPosition().y - 40);
		player1health.setString(std::to_string(player1.getHealth()));

		player2health.setPosition(player2.getPosition().x-10, player2.getPosition().y - 40);
		player2health.setString(std::to_string(player2.getHealth()));

		Window.draw(player1health);

		Window.draw(player2health);

		for (int i = 0; i < blocks.size(); i++)
		{
			blocks[i].Update(boundingbox);
			if (blocks[i].getAlive() == false && World.IsLocked() == false)
			{
				World.DestroyBody(blocks[i].getBody());
				blocks.erase(blocks.begin() + i);
		//		std::vector<Block>::iterator newEnd = std::remove(blocks.begin(), blocks.end(), i);
				
			}
		}

		if (Groundhit == true)
		{
		
				boundingbox.setPosition(sf::Vector2f(lastbulletpos.x - 50, lastbulletpos.y - 50));
			
			Groundhit = false;
		}

		

		//Window.draw(boundingbox);
	//	Window.draw(boundingbox);
		//for (int i = 0; i < blocks.size(); i++)
		//{
		//	Window.draw(blocks[i].getCircle());
		//}
		Window.display();
	
//		Window.draw(GroundSprite);
	}
	return 0;
}





