

#include "game_state.hpp"
#include "Play.hpp"

static  float SCALE = 30.f;
b2Vec2 Gravity(0.f, 10.0f);
b2World World(Gravity);
int numFootContacts;
int numFootContacts2;
bool player1hit = false;
bool player2hit = false;
bool Groundhit = false;




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

		if (fixtureUserDataA == "player1" || fixtureUserDataB == "player1")
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


		if (fixtureUserDataA == "player1" || fixtureUserDataB == "player1")
		{
			numFootContacts--;
		}
		else if (fixtureUserDataA == "player2" || fixtureUserDataB == "player2")
		{
			numFootContacts2--;
		}

		else if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "player1") ||
			(fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "player1"))//if A ROCKET HITS Player1
		{
			destroyRocket = true;
			player1hit = true;
		}
		else if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "player2") ||
			(fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "player2"))//if A ROCKET HITS Player2
		{
			destroyRocket = true;
			player2hit = true;
		}
		else if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "blocksensor") ||
			(fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "blocksensor"))//if A ROCKET HITS ground
		{
			Groundhit = true;
			destroyRocket = true;
		}
	}
};

MyContactListener myContactListenerInstance;

Play::Play(Game* game)
{
	this->game = game;

	 position = sf::Vector2f(400, 50);
	 font;
	 font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	
	game->window.setFramerateLimit(60);
    wormcount = 0;
	Player1Turn = true;
	water1.setPositon(sf::Vector2f(100, 100));
	player1health.setFont(font);
	player1health.setStyle(sf::Text::Bold);
	player1health.setPosition(0, 0);
	player1health.setCharacterSize(20);
	player1health.setColor(sf::Color::Black);

	player2health.setFont(font);
	player2health.setStyle(sf::Text::Bold);
	player2health.setPosition(0, 0);
	player2health.setCharacterSize(20);
	player2health.setColor(sf::Color::Black);

	dirttex.loadFromFile("Resources/grass/7.png");
	topStraighttex.loadFromFile("Resources/grass/6.png");
	leftStraighttex.loadFromFile("Resources/grass/8.png");
	topLeftCornertex.loadFromFile("Resources/grass/5.png");
	topRightCornertex.loadFromFile("Resources/grass/4.png");
	rightStraight.loadFromFile("Resources/grass/3.png");
	bottomStraight.loadFromFile("Resources/grass/1.png");
	bottomLeftCorner.loadFromFile("Resources/grass/2.png");

    sizeofmap = 0;
	RocketTexture.loadFromFile("Resources/Rocket.png");
	CrosshairTexture.loadFromFile("Resources/crosshair.png");
	backGroundTexture.loadFromFile("Resources/background.jpg");
	CharacterTexture.loadFromFile("Resources/weird.png");

	numFootContacts = 0;
   player1.Init(World, position, CharacterTexture, 1);
   player2.Init(World, position + sf::Vector2f(100, 0), CharacterTexture, 2);

     cross.Init(CrosshairTexture, position);
	player1Fire = false;
	player2Fire = false;

	background.setTexture(backGroundTexture);
	background.setPosition(sf::Vector2f(0, 00));

	World.SetContactListener(&myContactListenerInstance);
	boundingbox = sf::CircleShape(50);
	boundingbox.setPosition(-500, -500);
	boundingbox.setFillColor(sf::Color::Transparent);
	boundingbox.setOutlineThickness(5.f);
	boundingbox.setOutlineColor(sf::Color::Black);
	 //width = 200;
	 //height = 30;

	int map[30][200] = {
      #include "testtest.txt"
	};


	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 200; x++)
		{
			int c = map[y][x];
			if (c == 2 || c == 3 || c == 4 || c == 5 || c == 6 || c == 7 || c == 8 || c == 10)
			{
				Block temp = Block(map[y][x], sf::Vector2f(x, y), World);
				blocks.push_back(temp);
			}
		}

	}
	



	

}


void Play::draw()
{


	return;
}

void Play::update()
{
	World.Step(1 / 60.f, 8, 3);
	water1.Update();
	game->window.clear(sf::Color::Cyan);
	game->window.draw(background);
	UpdateStaticBodies();

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


	player1.UpdateSprite();
	player2.UpdateSprite();
	UpdateCamera();
	UpdateRockets();
	UpdateHealth();
	UpdateBlocks();
	
	game->window.draw(player1.getSprite());
	game->window.draw(player2.getSprite());
	game->window.draw(cross.getSprite());
	game->window.draw(player1health);
	game->window.draw(player2health);
	game->window.draw(boundingbox);
	water1.Draw(game);
	game->window.display();

	return;
}

void Play::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
			/* Resize the window */

		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();

			if (event.key.code == sf::Keyboard::E)
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
			if (event.key.code == sf::Keyboard::L)
			{
				Player1Turn = false;
			}
			if (event.key.code == sf::Keyboard::K)
			{
				Player1Turn = true;
			}

			break;
		}
		default: break;
		}
	}

	return;
}
void Play::UpdateStaticBodies()
{
	int BodyCount = 0;

	for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{

		if (BodyIterator->GetType() == b2_staticBody){

			if (BodyIterator->GetUserData() == "dirt"){
				sf::Sprite DirtSprite;
				DirtSprite.setTexture(dirttex);
				DirtSprite.setOrigin(0, 0);
				DirtSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				DirtSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(DirtSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "topStraight"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(topStraighttex);
				grassSprite.setOrigin(0, 0);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "leftStraight"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(leftStraighttex);
				grassSprite.setOrigin(0, 0);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "topLeftCorner"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(topLeftCornertex);
				grassSprite.setOrigin(0, 0);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "topRightCorner"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(topRightCornertex);
				grassSprite.setOrigin(0, 0);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "rightStraight"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(rightStraight);
				grassSprite.setOrigin(0, 0);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "bottomStraight"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(bottomStraight);
				grassSprite.setOrigin(0, 0);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "bottomLeftCorner"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(bottomLeftCorner);
				grassSprite.setOrigin(0, 0);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}

		}


	}
}
void Play::SwitchTurn()
{
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
void Play::UpdateCamera()
{

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
		game->window.setView(player1View);
		for (int i = 0; i < Rockets.size(); i++)
		{
			if (player1Fire == true)
			{
				game->window.setView(bulletView);
			}
		}
	}
	else if (Player1Turn == false)
	{
		game->window.setView(player2View);
		for (int i = 0; i < Rockets.size(); i++)
		{
			if (player2Fire == true)
			{
				game->window.setView(bulletView);
			}
		}
	}
}
void Play::UpdateRockets()
{
	for (int i = 0; i < Rockets.size(); i++)
	{

		Rockets[i].Update(World);
		if (Rockets[i].getPosition().x + 22 < 0 || Rockets[i].getPosition().x - 22 > (width * 20) || Rockets[i].getPosition().y > 600)
		{
			destroyRocket = true;
		}

		game->window.draw(Rockets[i].getSprite());
	}

	if (destroyRocket == true && World.IsLocked() == false)
	{
		for (int i = 0; i < Rockets.size(); i++)
		{
			lastbulletpos = Rockets[i].getPosition();
			World.DestroyBody(Rockets[i].getBody());
			Rockets.pop_back();
			destroyRocket = false;

			SwitchTurn();
		}
	}
}
void Play::UpdateHealth()
{

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

	player1health.setPosition(player1.getPosition().x - 10, player1.getPosition().y - 40);
	player1health.setString(std::to_string(player1.getHealth()));

	player2health.setPosition(player2.getPosition().x - 10, player2.getPosition().y - 40);
	player2health.setString(std::to_string(player2.getHealth()));

}
void Play::UpdateBlocks()
{
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

}