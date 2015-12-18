

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




		if (fixtureUserDataA == "player1foot" || fixtureUserDataB == "player1foot")
		{
			numFootContacts++;
		}
		if (fixtureUserDataA == "player2foot" || fixtureUserDataB == "player2foot")
		{
			numFootContacts2++;
		}
		 if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "player1Sensor") ||
			(fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "player1Sensor"))//if A ROCKET HITS Player1
		{
			destroyRocket = true;
			player1hit = true;
		}
		 if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "player2Sensor") ||
			(fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "player2Sensor"))//if A ROCKET HITS Player2
		{
			destroyRocket = true;
			player2hit = true;
		}

	}

	void EndContact(b2Contact* contact) {

		void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
		void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();


		if (fixtureUserDataA == "player1foot" || fixtureUserDataB == "player1foot")
		{
			numFootContacts--;
		}
		else if (fixtureUserDataA == "player2foot" || fixtureUserDataB == "player2foot")
		{
			numFootContacts2--;
		}

		//else if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "player1") ||
		//	(fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "player1"))//if A ROCKET HITS Player1
		//{
		//	destroyRocket = true;
		//	player1hit = true;
		//}
		//else if ((fixtureUserDataA == "rocketsensor" && fixtureUserDataB == "player2") ||
		//	(fixtureUserDataB == "rocketsensor" && fixtureUserDataA == "player2"))//if A ROCKET HITS Player2
		//{
		//	destroyRocket = true;
		//	player2hit = true;
		//}
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
	
	turn.setPosition(sf::Vector2f(300, -100));
	turn.setColor(sf::Color::Red);
	turn.setFont(font);
	turn.setStyle(sf::Text::Bold);
	turn.setCharacterSize(15);
	turnTimer = 10;

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
	gameSize = blockAmount * blockWidth;

	bullerTimer = 1.5f;
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
	outOfBounds = false;
	Explosion.setSmooth(true);
	ExplosionSprite.setTexture(Explosion);
	//Sprite.setOrigin(16.f, 16.f);
	ExplosionSprite.setOrigin(0, 0);
	ExplosionSprite.setTextureRect(sf::IntRect(Explosionsource.x * 128, Explosionsource.y * 128, 128, 128));

    sizeofmap = 0;
	RocketTexture.loadFromFile("Resources/Rocket.png");
	CrosshairTexture.loadFromFile("Resources/crosshair.png");
	backGroundTexture.loadFromFile("Resources/background.jpg");
	playerTexture.loadFromFile("Resources/player.png");
	player2Texture.loadFromFile("Resources/player2.png");

	buildViewenter = sf::Vector2f(400, 300);
	numFootContacts = 0;

	bulletOffset = 450;
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

	effectToggle = true;
	spacialToggle = true;
	backgroundToggle = false;
	reverbToggle = false;
	waveToggle = false;
	DopplerToggle = true;

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
	reverbCircle.setPosition(soundManager.getReverbPosition().x - 300, soundManager.getReverbPosition().y - 300);
	
	reverbCircle.setRadius(300);
	reverbCircle.setFillColor(sf::Color::Transparent);
	reverbCircle.setOutlineThickness(5.f);
	reverbCircle.setOutlineColor(sf::Color::Black);


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


	Firetexture.loadFromFile("Resources/smoke.png");
	Snowtexture.loadFromFile("Resources/snow.png");
	system.setTexture(Snowtexture);
	Snowemitter1.setEmissionRate(100);
	Snowemitter1.setParticleLifetime(thor::Distributions::uniform(sf::seconds(9), sf::seconds(12)));
	Snowemitter1.setParticlePosition(thor::Distributions::circle(sf::Vector2f(1000, -1000), 100));   // Emit particles in given circle
	Snowemitter1.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 200), 50.f)); // Emit towards direction with deviation of 15�
	Snowemitter1.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	system.addEmitter(Snowemitter1);

	Snowemitter2.setEmissionRate(100);
	Snowemitter2.setParticleLifetime(thor::Distributions::uniform(sf::seconds(9), sf::seconds(12)));
	Snowemitter2.setParticlePosition(thor::Distributions::circle(sf::Vector2f(200, -1000), 100));   // Emit particles in given circle
	Snowemitter2.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 200), 50.f)); // Emit towards direction with deviation of 15�
	Snowemitter2.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	system.addEmitter(Snowemitter2);

	Snowemitter3.setEmissionRate(100);
	Snowemitter3.setParticleLifetime(thor::Distributions::uniform(sf::seconds(9), sf::seconds(12)));
	Snowemitter3.setParticlePosition(thor::Distributions::circle(sf::Vector2f(1800, -1000), 100));   // Emit particles in given circle
	Snowemitter3.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 200), 50.f)); // Emit towards direction with deviation of 15�
	Snowemitter3.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	system.addEmitter(Snowemitter3);



	player1team.push_back(player1);
	player1team.push_back(player3);
	player2team.push_back(player2);
	player1Number = 0;
	player2Number = 0;
	
}

void Play::InitRocketParticle()
{
	Rocketsystem.setTexture(Firetexture);
	RocketEmitter.setEmissionRate(1000);
	RocketEmitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(0.1), sf::seconds(0.2)));
	RocketEmitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(300, 200), 5));   // Emit particles in given circle
	RocketEmitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(300, 500), 5.f)); // Emit towards direction with deviation of 15�
	RocketEmitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	Rocketsystem.addEmitter(thor::refEmitter(RocketEmitter));
	sf::IntRect rect0(0, 0, 10, 10);
	sf::IntRect rect1(10, 0, 10, 10);
	unsigned int index0 = system.addTextureRect(rect0);
	unsigned int index1 = system.addTextureRect(rect1);
	thor::UniversalEmitter emitter;
	emitter.setParticleTextureIndex(thor::Distributions::uniform(0, 2));
	//emitter.setParticleTextureIndex(index1);

}
void Play::UpdateRocketParticle()
{

	RocketEmitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(Rockets[0].getPosition().x, Rockets[0].getPosition().y), 5));
	RocketEmitter.setParticleVelocity(thor::Distributions::deflect(-(Rockets[0].getVelocity()), 10.f));


	Rocketsystem.update(RocketParticleclock.restart());
	game->window.draw(Rocketsystem);
}

void Play::draw()
{
	
	return;
}
void Play::DrawDebug()
{
	for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
	{
		if (BodyIterator->IsActive())
		{
			for (b2Fixture* b2Fixture = BodyIterator->GetFixtureList(); b2Fixture != 0; b2Fixture = b2Fixture->GetNext())
			{
				b2Shape::Type shapeType = b2Fixture->GetType();

				if (shapeType == b2Shape::e_polygon)
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)b2Fixture->GetShape();

					sf::ConvexShape sprite;
					int lenght = polygonShape->GetVertexCount();
					sprite.setPointCount(lenght);
					for (int i = 0; i < lenght; i++){
						sprite.setPoint(i, sf::Vector2f(polygonShape->GetVertex(i).x, polygonShape->GetVertex(i).y));
					}
					sprite.setFillColor(sf::Color(0, 0, 0, 0));
					sprite.setOutlineColor(sf::Color(0, 0, 0, 180));
					sprite.setOutlineThickness(-0.025f);
					sprite.setScale(30.f, 30.f);
					sprite.setOrigin(0, 0);
					sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
					sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
					game->window.draw(sprite);
				}
				
			}
		}
	}
}
void Play::update()
{




	system.update(Particleclock.restart());

	World.Step(1 / 60.f, 8, 3);

	
//	World.DrawDebugData();
	soundManager.update(playerPosition, playerVelocity, sf::Vector2f(playerPosition.x, 555));
	water1.Update();
	water2.Update();
	water3.Update();

	game->window.clear(sf::Color::Cyan);
	game->window.draw(background);
	game->window.draw(system);
	UpdateStaticBodies();
	UpdateCamera();

	if (Rockets.size() > 0)
	{
		UpdateRocketParticle();
	}
	bullerTimer -= clock.restart().asSeconds();
	if (CountDown == true )
	{
		
		bulletView.setCenter(lastbulletpos);
		game->window.setView(bulletView);

		

		if (bullerTimer <= 0)
		{
			bullerTimer = 1.5f;
			CountDown = false;
		}
	}

	if (BuildMode == false)
	{
		if (Player1Turn == true)
		{
			cross.Update(player1team[player1Number].getPosition());
			player1team[player1Number].Update(numFootContacts);
			playerVelocity = player1team[player1Number].getVelocity();
			playerPosition = player1team[player1Number].getPosition();
			turnTimer -= turnCLock.restart().asSeconds();
			turn.setString(" Player 1's turn, time remaining = " + std::to_string(turnTimer));

			game->window.setKeyRepeatEnabled(true);
		}
		else
		{
			turnTimer -= turnCLock.restart().asSeconds();
			game->window.setKeyRepeatEnabled(false);
			cross.Update(player2team[player2Number].getPosition());
			player2team[player2Number].Update(numFootContacts2);
			playerPosition = player2team[player2Number].getPosition();
			turn.setString("Player 2's turn, time remaining = " + std::to_string(turnTimer));

		}
		if (turnTimer <= 0 && player1Fire == false && player2Fire == false)
		{
			SwitchTurn();
		}
		if (player1team[player1Number].getPosition().x < 0 || player1team[player1Number].getPosition().x > 2000)
		{
			player1team[player1Number].setHealth(100);
		}
		else if (player2team[player2Number].getPosition().x < 0 || player2team[player2Number].getPosition().x > 2000)
		{
			player2team[player2Number].setHealth(100);
		}

		turn.setPosition(game->window.getView().getCenter().x - game->window.getView().getSize().x / 2, game->window.getView().getCenter().y - game->window.getView().getSize().y / 2);
		player1team[player1Number].UpdateSprite();
		player2team[player2Number].UpdateSprite();
		
		UpdateRockets();
		UpdateHealth();

		UpdateBlocks();

	}
	else
	{
		BuildModeUpdate();
	}
	
	game->window.draw(player1team[0].getSprite());
	game->window.draw(player1team[1].getSprite());
	game->window.draw(player2team[0].getSprite());
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

	//DrawDebug();
	if (soundManager.getReverbActive() == true)
	{
	//	game->window.draw(reverbCircle);
	//	game->window.draw(reverbCircle2);
	}
	game->window.draw(turn);
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
								Rocket tempRocket(World, cross.getPosition(), RocketTexture, player1team[player1Number].getPosition());
								Rockets.push_back(tempRocket);
								if (effectToggle == true)
								{
									soundManager.playFireSound();
								}
								
								InitRocketParticle();
								//soundManager.PlayRocket();
								overview = false;
							}
							//soundManager.PlayRocket();
							//RocketFired = true;
						}
						else
						{
							if (CountDown == false)
							{
								player2Fire = true;
								Rocket tempRocket(World, cross.getPosition(), RocketTexture, player2team[player2Number].getPosition());
								Rockets.push_back(tempRocket);
								if (effectToggle == true)
								{
									soundManager.playFireSound();
								}
								InitRocketParticle();
								//soundManager.PlayRocket();
								overview = false;
								//soundManager.PlayRocket();
							}
							//soundManager.PlayRocket();
							//RocketFired = true;
						}
					}

				}
			}
			if (event.key.code == sf::Keyboard::Num1)
			{
				if (effectToggle == true)
				{
					effectToggle = false;
					
				}
				else if (effectToggle == false)
				{
					effectToggle = true;
				}
				

			}
			if (event.key.code == sf::Keyboard::Num2)
			{
				if (backgroundToggle == true)
				{
					backgroundToggle = false;
					soundManager.pauseBackground(backgroundToggle);
				}
				else if (backgroundToggle == false)
				{
					backgroundToggle = true;
					soundManager.pauseBackground(backgroundToggle);
				}


			}
			if (event.key.code == sf::Keyboard::Num3)
			{
				if (waveToggle == true)
				{
					waveToggle = false;
					soundManager.pauseWave(waveToggle);
				}
				else if (waveToggle == false)
				{
					waveToggle = true;
					soundManager.pauseWave(waveToggle);
				}


			}
			if (event.key.code == sf::Keyboard::Num4)
			{
				if (reverbToggle == true)
				{
					reverbToggle = false;
					soundManager.ToggleReverb(reverbToggle);
				}
				else if (reverbToggle == false)
				{
					reverbToggle = true;
					soundManager.ToggleReverb(reverbToggle);
				}


			}
			if (event.key.code == sf::Keyboard::Num5)
			{
				if (spacialToggle == true)
				{
					spacialToggle = false;
					soundManager.ToggleTest(spacialToggle);
				}
				else if (spacialToggle == false)
				{
					spacialToggle = true;
					soundManager.ToggleTest(spacialToggle);
				}


			}
			if (event.key.code == sf::Keyboard::Num6)
			{
					soundManager.ToggleDoppler(0);

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
	
	if (Player1Turn == true)
	{
		player1Fire = false;
		Player1Turn = false;
		overview = false;
		turnTimer = 10;
		if ((player1Number + 1) < player1team.size())
		{
			player1Number++;
		}
		else
		{
			player1Number = 0;
		}
	
	}
	else if (Player1Turn == false)
	{
		player2Fire = false;
		Player1Turn = true;
		overview = false;
		turnTimer = 10;

		if ((player2Number + 1) < player2team.size())
		{
			player2Number++;
		}
		else
		{
			player2Number = 0;
		}
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
	
	

	player1team[0].Init(World, position, playerTexture, 1);
	player1team[1].Init(World, position + sf::Vector2f(100, 0), playerTexture, 1);
	player2team[0].Init(World, position + sf::Vector2f(1200, 0), player2Texture, 2);

	
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
		//	standardView.setCenter(player1.getPosition().x, player1.getPosition().y);
			standardView.setCenter(player1team[player1Number].getPosition().x, player1team[player1Number].getPosition().y);
			standardView.setSize(1500, 1125);
			game->window.setView(standardView);
		}


		if (overview == true && Player1Turn == false)
		{
			standardView.setCenter(player2team[player2Number].getPosition().x, player2team[player2Number].getPosition().y);
			standardView.setSize(1500, 1125);
			game->window.setView(standardView);
		}
		player1View.setSize(600, 450);
		player2View.setSize(600, 450);

		if (player1team[player1Number].getPosition().x > offset)
		{
			player1View.setCenter(sf::Vector2f(player1team[player1Number].getPosition()));// , sf::Vector2f(500, 500));#
		}
		else if (player1team[player1Number].getPosition().x  < offset&& player1team[player1Number].getPosition().x < gameSize - offset)
		{
			player1View.setCenter(sf::Vector2f(offset, player1team[player1Number].getPosition().y));
		}
		if (player1team[player1Number].getPosition().x  > gameSize - offset)
		{
			player1View.setCenter(sf::Vector2f(gameSize - offset, player1team[player1Number].getPosition().y));// , sf::Vector2f(500, 500));#
		}
		if (player2team[player2Number].getPosition().x > gameSize - offset)
		{
			player2View.setCenter(sf::Vector2f(gameSize - offset, player2team[player2Number].getPosition().y));// , sf::Vector2f(500, 500));#
		}

		if (player2team[player2Number].getPosition().x > offset && player2team[player2Number].getPosition().x < gameSize - offset)
		{
			player2View.setCenter(sf::Vector2f(player2team[player2Number].getPosition()));// , sf::Vector2f(500, 500));#
		}
		else if (player2team[player2Number].getPosition().x < offset)
		{
			player2View.setCenter(sf::Vector2f(offset, player2team[player2Number].getPosition().y));
		}



		if (Player1Turn == true && overview == false)
		{
			game->window.setView(player1View);

			for (int i = 0; i < Rockets.size(); i++)
			{
				if (player1Fire == true && overview == false)
				{
					/*if (Rockets[i].getPosition().x < 450 || Rockets[i].getPosition().x > 1545)
					{
					bullerTimer = 0;
					}*/

					if (Rockets[i].getPosition().x  < bulletOffset)
					{
						bulletView.setCenter(bulletOffset, Rockets[i].getPosition().y);
						bulletView.setSize(900, 675);
						game->window.setView(bulletView);
					}
					if (Rockets[i].getPosition().x  > bulletOffset &&  Rockets[i].getPosition().x < gameSize - bulletOffset)
					{
						bulletView.setCenter(sf::Vector2f(Rockets[i].getPosition()));
						bulletView.setSize(900, 675);
						game->window.setView(bulletView);
					}
					if (Rockets[i].getPosition().x  > gameSize  - bulletOffset)
					{
						
						bulletView.setCenter(gameSize-bulletOffset, Rockets[i].getPosition().y);
						bulletView.setSize(900, 675);
						game->window.setView(bulletView);
					}

				}
			}
		}
		else if (Player1Turn == false && overview == false)
		{
			game->window.setView(player2View);

			for (int i = 0; i < Rockets.size(); i++)
			{
				if (player2Fire == true && overview == false)
				{
					/*      if (Rockets[i].getPosition().x < 450 || Rockets[i].getPosition().x > 1545)
					{
					bullerTimer = 0;
					}*/
					if (Rockets[i].getPosition().x  < bulletOffset)
					{
						bulletView.setCenter(bulletOffset, Rockets[i].getPosition().y);
						bulletView.setSize(900, 675);
						game->window.setView(bulletView);
					}
					if (Rockets[i].getPosition().x  > bulletOffset &&  Rockets[i].getPosition().x < gameSize - bulletOffset)
					{
						bulletView.setCenter(sf::Vector2f(Rockets[i].getPosition()));
						bulletView.setSize(900, 675);
						game->window.setView(bulletView);
					}
					if (Rockets[i].getPosition().x  > gameSize - bulletOffset)
					{

						bulletView.setCenter(gameSize - bulletOffset, Rockets[i].getPosition().y);
						bulletView.setSize(900, 675);
						game->window.setView(bulletView);
					}
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
		if (Rockets[i].getPosition().x + 22 < 0 || Rockets[i].getPosition().x - 22 > (gameSize) || Rockets[i].getPosition().y > 600)
		{
			destroyRocket = true;
		//	bullerTimer = 1.5f;
			RocketFired = false;
			outOfBounds = true;
			//soundManager.StopRocket();

		}
		else
		{
			outOfBounds = false;
		}

		game->window.draw(Rockets[i].getSprite());
	}

	if (destroyRocket == true)// && World.IsLocked() == false)
	{
		if (effectToggle == true)
		{
			soundManager.playExplosionSound(Rockets[0].getPosition());
		}
		
		bullerTimer = 1.5f;
		startExplosion = true;
		if (outOfBounds == false)
		{
			CountDown = true;
		}

		
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
		player1team[player1Number].setHealth(20);
		player1hit = false;
	}
	if (player2hit == true)
	{
		player2team[player2Number].setHealth(20);
		player2hit = false;
	}

	player1health.setPosition(player1team[player1Number].getPosition().x - 10, player1team[player1Number].getPosition().y - 40);
	player1health.setString(std::to_string(player1team[player1Number].getHealth()));

	player2health.setPosition(player2team[player2Number].getPosition().x - 10, player2team[player2Number].getPosition().y - 40);
	player2health.setString(std::to_string(player2team[player2Number].getHealth()));

	if (player1team[player1Number].getHealth() == 0)
	{
	    
		game->pushState(new GameOver(this->game,"Player 2 Wins"));
	}
	else if (player2team[player2Number].getHealth() == 0)
	{
		game->pushState(new GameOver(this->game, "Player 1 Wins"));
	}

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



