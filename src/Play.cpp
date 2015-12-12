

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
		else if (fixtureUserDataA == "rocketsensor" || fixtureUserDataB == "rocketsensor")//if A ROCKET HITS ANYTHING
		{
			//	destroyRocket = true;
		}
	}
	void PreSolve(b2Contact* contact)
	{


	}
};

MyContactListener myContactListenerInstance;

Play::Play(Game* game)
{
	this->game = game;
	
	 position = sf::Vector2f(500, -50);
	 font;
	 font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	 BuildMode = true;
	 PlaceMode = false;
	 mousereleased = true;
	game->window.setFramerateLimit(60);
    wormcount = 0;
	zoomed = false;
	Player1Turn = true;
	RocketFired = false;
	water1.setPositon(sf::Vector2f(0, 555));
	water2.setPositon(sf::Vector2f(707, 555));
	water3.setPositon(sf::Vector2f(1414, 555));
	blockWidth = 20;
	blockAmount = 100;
	offset = 310;
	gameSize = blockAmount * blockWidth +50;
	gameSize = gameSize - offset;
	bullerTimer = 10.f;
	CountDown = false;
	explosiontimer = 5.0f;
	buildView.setSize(800, 600);
	dirttex.loadFromFile("Resources/snow/8.png");
	topStraighttex.loadFromFile("Resources/snow/6.png");
	leftStraighttex.loadFromFile("Resources/snow/9.png");
	topLeftCornertex.loadFromFile("Resources/snow/7.png");
	topRightCornertex.loadFromFile("Resources/snow/4.png");
	bottomRightCornertex.loadFromFile("Resources/snow/3.png");
	rightStraight.loadFromFile("Resources/snow/5.png");
	bottomStraight.loadFromFile("Resources/snow/2.png");
	bottomLeftCorner.loadFromFile("Resources/snow/1.png");
	Explosion.loadFromFile("Resources/explosion.png");

	Explosion.setSmooth(true);
	ExplosionSprite.setTexture(Explosion);
	//Sprite.setOrigin(16.f, 16.f);
	ExplosionSprite.setOrigin(0, 0);
	ExplosionSprite.setTextureRect(sf::IntRect(Explosionsource.x * 128, Explosionsource.y * 128, 128, 128));

    sizeofmap = 0;
	RocketTexture.loadFromFile("Resources/Rocket.png");
	CrosshairTexture.loadFromFile("Resources/crosshair.png");
	backGroundTexture.loadFromFile("Resources/background.jpg");
	CharacterTexture.loadFromFile("Resources/player.png");

	buildViewenter = sf::Vector2f(400, 300);
	numFootContacts = 0;


	player1Fire = false;
	player2Fire = false;

	background.setTexture(backGroundTexture);
	background.scale(1.5,1.3);
	background.setPosition(sf::Vector2f(-300,-500));

	World.SetContactListener(&myContactListenerInstance);
	boundingbox = sf::CircleShape(50);
	boundingbox.setPosition(-500, -500);
	boundingbox.setFillColor(sf::Color::Transparent);
	boundingbox.setOutlineThickness(5.f);
	boundingbox.setOutlineColor(sf::Color::Black);

	
	////////HUD
	hudPanelTex.loadFromFile("Resources/hudPanel.png");
	FinishButtonTexture.loadFromFile("Resources/finish.png");
	HudSprite.setTexture(hudPanelTex);
	HudSpritePosition = sf::Vector2f(0, 450);
	DirtBlockHud.setTexture(dirttex);
	FinishButtonSprite.setTexture(FinishButtonTexture);
    CurrentPlayer1Money = 1000;
	CurrentPlayer2Money = 1000;
	dirtPrice.setFont(font);
	dirtPrice.setStyle(sf::Text::Bold);
	dirtPrice.setCharacterSize(10);
	dirtPrice.setColor(sf::Color::Black);
	dirtPrice.setString("100");
	currentPlayer.setFont(font);
	currentPlayer.setStyle(sf::Text::Bold);
	currentPlayer.setCharacterSize(20);
	currentPlayer.setColor(sf::Color::Black);
	Money.setFont(font);
	Money.setStyle(sf::Text::Bold);
	Money.setCharacterSize(20);
	Money.setColor(sf::Color::Black);
	overview = false;
	///////////////////////////////////
	int map[30][100] = {
      #include "testlevel.txt"
	};


	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			int c = map[y][x];
			if (c == 1 || c == 2 || c == 3 || c == 4 || c == 5 || c == 6 || c == 7 || c == 8 || c ==9)
			{
				Block temp = Block(map[y][x], sf::Vector2f(x*20, y*20), World);
				blocks.push_back(temp);
			}
		}

	}
	SFMLDebugDraw debugDraw(game->window);
	World.SetDebugDraw(&debugDraw);
	debugDraw.SetFlags(b2Draw::e_shapeBit);
	//textures.loadFromFile("Resources/grass1.jpg");
	//system.setTexture(textures);
	emitter.setEmissionRate(30);
	emitter.setParticleLifetime(sf::seconds(5));
	system.addEmitter(emitter);
	emitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(5), sf::seconds(7)));
	emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(100,100), 10.f));   // Emit particles in given circle
	emitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 1), 15.f)); // Emit towards direction with deviation of 15°
	emitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly

	
}


void Play::draw()
{
 	game->window.draw(system);
	//World.DrawDebugData();
	return;
}

void Play::update()
{
	system.update(Pclock.restart());
	World.Step(1 / 60.f, 8, 3);

	soundManager.update(playerPosition, playerVelocity, sf::Vector2f(playerPosition.x, 555));
	water1.Update();
	water2.Update();
	water3.Update();

	game->window.clear(sf::Color::Cyan);
	game->window.draw(background);
	UpdateStaticBodies();
	UpdateCamera();
	sf::Event event;

	if (CountDown == true )
	{
		
		bulletView.setCenter(lastbulletpos);
		game->window.setView(bulletView);
		bullerTimer -= clock.restart().asSeconds();
		if (bullerTimer <= 0)
		{
			bullerTimer = 10.f;
			CountDown = false;
		}
	}

	if (BuildMode == false)
	{
		if (Player1Turn == true)
		{
			cross.Update(player1.getPosition());
			player1.Update(numFootContacts);
			playerVelocity = player1.getVelocity();
			playerPosition = player1.getPosition();
			//if (RocketFired == true)
			//{
			//	//soundManager.updatRocketSound(Rockets[0].getPosition(), Rockets[0].getVelocity(),playerPosition);
			//}
			game->window.setKeyRepeatEnabled(true);
		}
		else
		{
			game->window.setKeyRepeatEnabled(false);
			cross.Update(player2.getPosition());
			player2.Update(numFootContacts2);
	/*		if (RocketFired == true)
			{
				soundManager.updatRocketSound(playerPosition, playerVelocity, Rockets[0].getPosition());
			}*/
		}


		player1.UpdateSprite();
		player2.UpdateSprite();
		
		UpdateRockets();
		UpdateHealth();

		UpdateBlocks();

	}
	else
	{
		BuildModeUpdate();
	}
	
	game->window.draw(player1.getSprite());
	game->window.draw(player2.getSprite());
	game->window.draw(cross.getSprite());
	game->window.draw(player1health);
	game->window.draw(player2health);
	game->window.draw(boundingbox);
	water1.Draw(game);
	water2.Draw(game);
	water3.Draw(game);
	
	if (BuildMode == true)
	{
		game->window.draw(HudSprite);
		game->window.draw(DirtBlockHud);
		game->window.draw(FinishButtonSprite);
		game->window.draw(currentPlayer);
		game->window.draw(Money);
		game->window.draw(dirtPrice);
		if (PlaceMode == true)
		{
			game->window.draw(placingSprite);
		}
	}
	if (startExplosion == true)
	{
		PlayExplosion();
		game->window.draw(ExplosionSprite);
	}
	//game->window.draw(system);
	game->window.display();

	return;
}
void Play::PlayExplosion()
{
	ExplosionSprite.setPosition(lastbulletpos.x -64 , lastbulletpos.y-64);
	//Sprite.setRotation(m_body->GetAngle() * 180 / b2_pi);


	explosiontimer++;
	if (explosiontimer >= 2)
	{
		Explosionsource.x++;
		if (Explosionsource.x > 4){

			Explosionsource.x = 0;
			Explosionsource.y++;
		}
		if (Explosionsource.y > 4)
		{
			Explosionsource.x = 0;
			Explosionsource.y = 0;
			startExplosion = false;
		}
		explosiontimer = 0;
	}

	ExplosionSprite.setTextureRect(sf::IntRect(Explosionsource.x * 128, Explosionsource.y * 128, 128, 128));

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
				if (BuildMode == false)
				{
					if (Rockets.size() < 1)
					{
						if (Player1Turn == true)
						{
							if (CountDown == false)
							{
								player1Fire = true;
								Rocket tempRocket(World, cross.getPosition(), RocketTexture, player1.getPosition());
								Rockets.push_back(tempRocket);
								soundManager.playFireSound();
							}
							//soundManager.PlayRocket();
							//RocketFired = true;
						}
						else
						{
							if (CountDown == false)
							{
								player2Fire = true;
								Rocket tempRocket(World, cross.getPosition(), RocketTexture, player2.getPosition());
								Rockets.push_back(tempRocket);
								soundManager.playFireSound();
							}
							//soundManager.PlayRocket();
							//RocketFired = true;
						}
					}

				}
			}
			if (event.key.code == sf::Keyboard::Z)
			{
				if (zoomed == false)
				{
					overview = true;
				}
			}

			if (event.key.code == sf::Keyboard::X)
			{

				overview = false;
			}
		/*	if (event.key.code == sf::Keyboard::L)
			{
				Player1Turn = false;
			}
			if (event.key.code == sf::Keyboard::K)
			{
				Player1Turn = true;
			}*/
			if (event.key.code == sf::Keyboard::Left && BuildMode == true)
			{
				buildViewenter.x -= 20;
				HudSpritePosition.x -= 20;
			}
			if (event.key.code == sf::Keyboard::Right && BuildMode == true)
			{
				buildViewenter.x += 20;
				HudSpritePosition.x += 20;
			}
			if (event.key.code == sf::Keyboard::Up && BuildMode == true)
			{
				buildViewenter.y -= 20;
				HudSpritePosition.y -= 20;
			}
			if (event.key.code == sf::Keyboard::Down && BuildMode == true)
			{
				buildViewenter.y += 20;
				HudSpritePosition.y += 20;
			}

			break;
		}
		case sf::Event::MouseButtonReleased:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					mousereleased = true;
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
				DirtSprite.setOrigin(10, 10);
				DirtSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				DirtSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(DirtSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "topStraight"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(topStraighttex);
				grassSprite.setOrigin(10, 10);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "leftStraight"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(leftStraighttex);
				grassSprite.setOrigin(10,10);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "topLeftCorner"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(topLeftCornertex);
				grassSprite.setOrigin(10, 10);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "topRightCorner"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(topRightCornertex);
				grassSprite.setOrigin(10, 10);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "rightStraight"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(rightStraight);
				grassSprite.setOrigin(10, 10);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "bottomStraight"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(bottomStraight);
				grassSprite.setOrigin(10, 10);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "bottomLeftCorner"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(bottomLeftCorner);
				grassSprite.setOrigin(10, 10);
				grassSprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				grassSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(grassSprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "bottomRightCorner"){
				sf::Sprite grassSprite;
				grassSprite.setTexture(bottomRightCornertex);
				grassSprite.setOrigin(10, 10);
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
	
	if (Player1Turn == true )
	{
		player1Fire = false;
		Player1Turn = false;
		
	}
	else if (Player1Turn == false  )
	{
		player2Fire = false;
		Player1Turn = true;
		
	}

}
void Play::BuildModeUpdate()
{
	HudSprite.setPosition(HudSpritePosition);
	DirtBlockHud.setPosition(HudSpritePosition + sf::Vector2f(100, 50));
	FinishButtonSprite.setPosition(HudSpritePosition + sf::Vector2f(350, 100));
	sf::Vector2i windowPosition = sf::Vector2i(buildView.getCenter().x - 400, buildView.getCenter().y - 300);
	sf::Vector2i position = sf::Mouse::getPosition(game->window) + windowPosition;


	dirtPrice.setPosition(DirtBlockHud.getPosition() + sf::Vector2f(0,20));

	if (Player1Turn == true)
	{
	
		currentPlayer.setString("PLAYER 1  ");
		currentPlayer.setPosition(HudSpritePosition + sf::Vector2f(10, 10));
		Money.setString(std::to_string(CurrentPlayer1Money) + " Credits Remaining");
		Money.setPosition(HudSpritePosition + sf::Vector2f(110, 10));


	}
	else if (Player1Turn == false)
	{

		currentPlayer.setString("PLAYER 2  ");
		currentPlayer.setPosition(HudSpritePosition + sf::Vector2f(10, 10));
		Money.setString(std::to_string(CurrentPlayer2Money) + " Credits Remaining");
		Money.setPosition(HudSpritePosition + sf::Vector2f(110, 10));

	}

	if (PlaceMode == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mousereleased == true)
		{
			PlaceMode = false;
		}

		if (currentType == 8)
		{
			placingSprite.setTexture(dirttex);
			price = 100;
		}

		placingSprite.setPosition(sf::Vector2f(position.x - 10, position.y - 10));



		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousereleased == true)
		{
			if ( Player1Turn == true && CurrentPlayer1Money >= price)
			{
				mousereleased = false;
				Block temp = Block(currentType, sf::Vector2f(position.x , position.y), World);
				blocks.push_back(temp);
				CurrentPlayer1Money -= price;
			}
			else if (Player1Turn == false && CurrentPlayer2Money >= price)
			{
				mousereleased = false;
				Block temp = Block(currentType, sf::Vector2f(position.x , position.y ), World);
				blocks.push_back(temp); 
				CurrentPlayer2Money -= price;
			}

		}

	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousereleased == true)
	{
	
		mousereleased = false;

		if (CheckClicked(DirtBlockHud, position) == true)
		{
			{
				currentType = 8;
				PlaceMode = true;
			}
		}
	
		else if (CheckClicked(FinishButtonSprite, position)==true)
		{
			if (Player1Turn == true)
			{
				Player1Turn = false;

			}
			else if (Player1Turn == false)
			{
				GameStart();
			}

		}
		



	}



	
}
void Play::GameStart()
{
	
	BuildMode = false;

	Player1Turn = true;
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
	
	player1.Init(World, position, CharacterTexture, 1);
	player2.Init(World, position + sf::Vector2f(100, 0), CharacterTexture, 2);
	cross.Init(CrosshairTexture, position);


}
bool Play::CheckClicked(sf::Sprite sprite, sf::Vector2i position)
{

	if (position.x > sprite.getGlobalBounds().left
		&& position.x < (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width)
		&& position.y > sprite.getGlobalBounds().top
		&& position.y < (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height))
	{
		return true;
	}
	else
		return false;
}
void Play::UpdateCamera()
{
	if (BuildMode == false)
	{
		
		if (overview == true && Player1Turn == true)
		{
			standardView.setCenter(player1.getPosition().x, player1.getPosition().y);
			standardView.setSize(1500, 1125);
			game->window.setView(standardView);
		}


		if (overview == true && Player1Turn == false)
		{
			standardView.setCenter(player2.getPosition().x, player2.getPosition().y);
			standardView.setSize(1500, 1125);
			game->window.setView(standardView);
		}
		player1View.setSize(600, 450);
		player2View.setSize(600, 450);
		if (player1.getPosition().x  > offset)
		{
			player1View.setCenter(sf::Vector2f(player1.getPosition()));// , sf::Vector2f(500, 500));#
		}
		else if (player1.getPosition().x  < offset)
		{
			player1View.setCenter(sf::Vector2f(offset, player1.getPosition().y));
		}
		if (player1.getPosition().x  > gameSize)
		{
			player1View.setCenter(sf::Vector2f(gameSize, player1.getPosition().y));// , sf::Vector2f(500, 500));#
		}
		if (player2.getPosition().x  > gameSize)
		{
			player2View.setCenter(sf::Vector2f(gameSize, player2.getPosition().y));// , sf::Vector2f(500, 500));#
		}

		if (player2.getPosition().x  > offset && player2.getPosition().x < gameSize)
		{
			player2View.setCenter(sf::Vector2f(player2.getPosition()));// , sf::Vector2f(500, 500));#
		}
		else if (player2.getPosition().x  < offset && player2.getPosition().x < gameSize)
		{
			player2View.setCenter(sf::Vector2f(offset, player2.getPosition().y));
		}

		

		if (Player1Turn == true && overview == false )
		{
			
			
				game->window.setView(player1View);
			
			
			for (int i = 0; i < Rockets.size(); i++)
			{
				if (player1Fire == true && overview == false)
				{
					if (Rockets[i].getPosition().x < gameSize - offset)
					{
						bulletView.setCenter(sf::Vector2f(Rockets[i].getPosition()));
						bulletView.setSize(900, 675);
					}
					game->window.setView(bulletView);
				}
			}
		}
		else if (Player1Turn == false && overview == false )
		{
			
				game->window.setView(player2View);
			
			
			for (int i = 0; i < Rockets.size(); i++)
			{
				if (player2Fire == true && overview == false)
				{
					if (Rockets[i].getPosition().x < gameSize - offset)
					{
						bulletView.setCenter(sf::Vector2f(Rockets[i].getPosition()));
						bulletView.setSize(900, 675);
					}
					game->window.setView(bulletView);
				}
			}
		}
	}
	else
	{
		buildView.setCenter(buildViewenter);
		game->window.setView(buildView);
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
			
			RocketFired = false;
			//soundManager.StopRocket();

		}

		game->window.draw(Rockets[i].getSprite());
	}

	if (destroyRocket == true)// && World.IsLocked() == false)
	{
		startExplosion = true;
		CountDown = true;
		for (int i = 0; i < Rockets.size(); i++)
		{

			lastbulletpos = Rockets[i].getPosition();
			World.DestroyBody(Rockets[i].getBody());
			Rockets.pop_back();
			destroyRocket = false;
			RocketFired = false;
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
	//	blocks[i].Update(boundingbox);
		if (blocks[i].getAlive() == false && World.IsLocked() == false)
		{
			World.DestroyBody(blocks[i].getBody());
			blocks.erase(blocks.begin() + i);
			//		std::vector<Block>::iterator newEnd = std::remove(blocks.begin(), blocks.end(), i);

		}
	}

	if (Groundhit == true)
	{
		
		boundingbox.setPosition(sf::Vector2f(lastbulletpos.x -50 , lastbulletpos.y-50));
		for (int i = 0; i < blocks.size(); i++)
		{
			if (CollisionManager::CircleDetectCollision(blocks[i].getCircle(), boundingbox) ==true)
			{
				blocks[i].CheckLives();
			}
		

		}
		boundingbox.setPosition(-500, -500);

		Groundhit = false;
	}

}



