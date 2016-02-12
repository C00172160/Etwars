

#include "game_state.hpp"
#include "Play.hpp"

static  float SCALE = 30.f;



int numFootContacts;
int numFootContacts2;
int player1footid;
int player2footid;

bool player1hit = false;
bool player2hit = false;
bool Groundhit = false;

bool captain1hit = false;
bool captain2hit = false;


sf::Vector2f lastbulletpos;
bool destroyRocket = false;


class MyContactListener : public b2ContactListener
{

	void BeginContact(b2Contact* contact) {
		//check if fixture A was the foot sensor
		void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
		void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();


		if (fixtureUserDataA == (void*)player1footid || fixtureUserDataB == (void*)player1footid)
		{
			numFootContacts++;
		}
		if (fixtureUserDataA == (void*)player2footid || fixtureUserDataB == (void*)player2footid)
		{
			numFootContacts2++;
		}


	}

	void EndContact(b2Contact* contact) {

		void* fixtureUserDataA = contact->GetFixtureA()->GetUserData();
		void* fixtureUserDataB = contact->GetFixtureB()->GetUserData();



		if (fixtureUserDataA == (void*)player1footid || fixtureUserDataB == (void*)player1footid)
		{
			numFootContacts--;
		}
		if (fixtureUserDataA == (void*)player2footid || fixtureUserDataB == (void*)player2footid)
		{
			numFootContacts2--;
		}


	}
	void PreSolve(b2Contact* contact)
	{


	}
};

MyContactListener myContactListenerInstance;




Play::Play(Game* game) : World(b2Vec2(0.f, 10.0f))
{

	
	this->game = game;
	changeState = false;
	turn.setPosition(sf::Vector2f(300, -100));
	turn.setColor(sf::Color::Red);
	turn.setFont(font);
	turn.setStyle(sf::Text::Bold);
	turn.setCharacterSize(15);
	turnTimer = 15;

	 position = sf::Vector2f(500, -50);
	 font;
	 font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	 BuildMode = true;
	 PlaceBlockMode = false;
	 PlacePlayerMode = false;
	 mousereleased = true;
	game->window.setFramerateLimit(60);
    
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
	captainplacemode = true;
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
	shotgunBulletTex.loadFromFile("Resources/shotgunbullet.png");
	sniperBullettex.loadFromFile("Resources/sniperbullet.png");
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
	captainTexture1.loadFromFile("Resources/captain1Right.png");
	captaintexture2.loadFromFile("Resources/captain2Left.png");
	HandgunBulletTexture.loadFromFile("Resources/handgunbullet.png");
	handguntex.loadFromFile("Resources/handgun.png");
	shotguntex.loadFromFile("Resources/shotgun.png");
	snipertex.loadFromFile("Resources/sniper.png");

	rocketlaunchertex.loadFromFile("Resources/RocketLAuncher.png");
	handgunplayer1.loadFromFile("Resources/handgunplayer1.png");
	handgunplayer2.loadFromFile("Resources/handgunplayer2.png");
	shotgunplayer1.loadFromFile("Resources/shotgunplayer1.png");
	shotgunplayer2.loadFromFile("Resources/shotgunplayer2.png");
	sniperplayer1.loadFromFile("Resources/sniperplayer1.png");
	sniperplayer2.loadFromFile("Resources/sniperplayer2.png");

	steelblock.loadFromFile("Resources/steel.png");
	concreteblock.loadFromFile("Resources/concrete.png");

	buildViewenter = sf::Vector2f(400, 300);
	numFootContacts = 0;

	bulletOffset = 450;
	player1Fire = false;
	player2Fire = false;

	background.setTexture(backGroundTexture);
	background.scale(1.5,1.3);
	background.setPosition(sf::Vector2f(-300,-500));

	World.SetContactListener(&myContactListenerInstance);
	boundingbox = sf::CircleShape(75);
	
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
	RocketPlayerTexture.loadFromFile("Resources/RocketPlayerTexture.png");
	RocketPlayerTexture2.loadFromFile("Resources/RocketPlayerTexture2.png");


	HudSprite.setTexture(hudPanelTex);
	HudSpritePosition = sf::Vector2f(0, 450);
	
	DirtBlockHud.setTexture(dirttex);
	concreteblockhud.setTexture(concreteblock);
	steelblockhud.setTexture(steelblock);
	RocketPlayerSprite.setTexture(RocketPlayerTexture);

	rocketPrice = 500;
	shotgunPrice = 350;
	sniperPrice = 450;
	handgunPrice = 200;
	dirtprice = 50;
	steelPrice = 150;
	concretePrice = 100;

	FinishButtonSprite.setTexture(FinishButtonTexture);
    CurrentPlayer1Money = 1000;
	CurrentPlayer2Money = 1000;

	dirtPriceText.setFont(font);
	dirtPriceText.setStyle(sf::Text::Bold);
	dirtPriceText.setCharacterSize(20);
	dirtPriceText.setColor(sf::Color::Black);
	dirtPriceText.setString(to_string(dirtprice));


	dirtName.setFont(font);
	dirtName.setStyle(sf::Text::Bold);
	dirtName.setCharacterSize(20);
	dirtName.setColor(sf::Color::Black);
	dirtName.setString("Dirt");

	concretepriceText.setFont(font);
	concretepriceText.setStyle(sf::Text::Bold);
	concretepriceText.setCharacterSize(20);
	concretepriceText.setColor(sf::Color::Black);
	concretepriceText.setString(to_string(concretePrice));

	concreteName.setFont(font);
	concreteName.setStyle(sf::Text::Bold);
	concreteName.setCharacterSize(20);
	concreteName.setColor(sf::Color::Black);
	concreteName.setString("Concrete");

	steelpriceText.setFont(font);
	steelpriceText.setStyle(sf::Text::Bold);
	steelpriceText.setCharacterSize(20);
	steelpriceText.setColor(sf::Color::Black);
	steelpriceText.setString(to_string(steelPrice));

	steelName.setFont(font);
	steelName.setStyle(sf::Text::Bold);
	steelName.setCharacterSize(20);
	steelName.setColor(sf::Color::Black);
	steelName.setString("Steel");

	HandgunPriceText.setFont(font);
	HandgunPriceText.setStyle(sf::Text::Bold);
	HandgunPriceText.setCharacterSize(20);
	HandgunPriceText.setColor(sf::Color::Black);
	HandgunPriceText.setString(to_string(handgunPrice));


	handgunName.setFont(font);
	handgunName.setStyle(sf::Text::Bold);
	handgunName.setCharacterSize(20);
	handgunName.setColor(sf::Color::Black);
	handgunName.setString("Handgun");

	ShotgunPriceText.setFont(font);
	ShotgunPriceText.setStyle(sf::Text::Bold);
	ShotgunPriceText.setCharacterSize(20);
	ShotgunPriceText.setColor(sf::Color::Black);
	ShotgunPriceText.setString(to_string(shotgunPrice));

	shotgunName.setFont(font);
	shotgunName.setStyle(sf::Text::Bold);
	shotgunName.setCharacterSize(20);
	shotgunName.setColor(sf::Color::Black);
	shotgunName.setString("Shotgun");

	SniperPriceText.setFont(font);
	SniperPriceText.setStyle(sf::Text::Bold);
	SniperPriceText.setCharacterSize(20);
	SniperPriceText.setColor(sf::Color::Black);
	SniperPriceText.setString(to_string(sniperPrice));

	sniperName.setFont(font);
	sniperName.setStyle(sf::Text::Bold);
	sniperName.setCharacterSize(20);
	sniperName.setColor(sf::Color::Black);
	sniperName.setString("Sniper");

	RocketPlayerPriceText.setFont(font);
	RocketPlayerPriceText.setStyle(sf::Text::Bold);
	RocketPlayerPriceText.setCharacterSize(20);
	RocketPlayerPriceText.setColor(sf::Color::Black);
	RocketPlayerPriceText.setString(to_string(rocketPrice));

	rocketName.setFont(font);
	rocketName.setStyle(sf::Text::Bold);
	rocketName.setCharacterSize(20);
	rocketName.setColor(sf::Color::Black);
	rocketName.setString("Rocket");

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
	

	placingspriteCircle.setFillColor(sf::Color::Black);
	//placingspriteCircle.setOrigin(20, 20);
	placingspriteCircle.setPosition(sf::Vector2f(-500, -500));
	placingspriteCircle.setRadius(20);
	reverbCircle.setRadius(300);
	reverbCircle.setFillColor(sf::Color::Transparent);
	reverbCircle.setOutlineThickness(5.f);
	reverbCircle.setOutlineColor(sf::Color::Black);
	captain1placed = false; 
	capatain2placed = false;

	captain1health.setFont(font);
	captain1health.setColor(sf::Color::Black);
	captain1health.setStyle(sf::Text::Bold);
	captain1health.setCharacterSize(20);


	captain2health.setFont(font);
	captain2health.setColor(sf::Color::Black);
	captain2health.setStyle(sf::Text::Bold);
	captain2health.setCharacterSize(20);

	PlaceCaptaintext.setFont(font);
	PlaceCaptaintext.setColor(sf::Color::Black);
	PlaceCaptaintext.setStyle(sf::Text::Bold || sf::Text::Italic);
	PlaceCaptaintext.setCharacterSize(40);
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
	Snowemitter1.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 200), 50.f)); // Emit towards direction with deviation of 15°
	Snowemitter1.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	system.addEmitter(Snowemitter1);

	Snowemitter2.setEmissionRate(100);
	Snowemitter2.setParticleLifetime(thor::Distributions::uniform(sf::seconds(9), sf::seconds(12)));
	Snowemitter2.setParticlePosition(thor::Distributions::circle(sf::Vector2f(200, -1000), 100));   // Emit particles in given circle
	Snowemitter2.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 200), 50.f)); // Emit towards direction with deviation of 15°
	Snowemitter2.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	system.addEmitter(Snowemitter2);

	Snowemitter3.setEmissionRate(100);
	Snowemitter3.setParticleLifetime(thor::Distributions::uniform(sf::seconds(9), sf::seconds(12)));
	Snowemitter3.setParticlePosition(thor::Distributions::circle(sf::Vector2f(1800, -1000), 100));   // Emit particles in given circle
	Snowemitter3.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(0, 200), 50.f)); // Emit towards direction with deviation of 15°
	Snowemitter3.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	system.addEmitter(Snowemitter3);

	
	players1Teamselected = false;//if player one has bought any players
	players2TeamSeleced = false;

	player1team.push_back(player1);

	player2team.push_back(player2);
	player1Number = 0;
	player2Number = 0;

	player1team[0] =  Player(numberPlayersTeam1, World, position, playerTexture, 1, 1);

	player2team[0] = Player(numberPlayersTeam2, World, position + sf::Vector2f(1200, 0), player2Texture, 2, 1);

} 
void Play::InitRocketParticle()
{
	Rocketsystem.setTexture(Firetexture);
	RocketEmitter.setEmissionRate(1000);
	RocketEmitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(0.1), sf::seconds(0.2)));
	RocketEmitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(300, 200), 5));   // Emit particles in given circle
	RocketEmitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(300, 500), 5.f)); // Emit towards direction with deviation of 15°
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
			if (BodyIterator->GetType() == b2_dynamicBody)
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
}

void Play::update()
{
	for (int i = 0; i < player1team.size();i++)
	{
		if (player1team[i].getAlive() == true)
		{
			break;
		}
		else if (i+1 >= player1team.size() && player1team[i].getAlive() == false)
		{
			player1teamdead = true;
		}
	}
	for (int i = 0; i < player2team.size();i++)
	{
		for (int i = 0; i < player2team.size(); i++)
		{
			if (player2team[i].getAlive() == true)
			{
				break;
			}
			else if (i + 1 >= player2team.size() && player2team[i].getAlive() == false)
			{
				player2teamdead = true;
			}
		}
	}
	if (player1teamdead == false)
	{
		if (player1team[player1Number].getAlive() == false)
		{
			if (player1Number + 1 < player1team.size())
			{
				player1Number++;
			}
			else if (player1Number + 1 >= player1team.size())
			{
				player1Number = 0;
			}
		}
	}
	if (player2teamdead == false)
	{

		if (player2team[player2Number].getAlive() == false)
		{
			if (player2Number + 1 < player2team.size())
			{
				player2Number++;
			}
			else if (player2Number + 1 >= player2team.size())
			{
				player2Number = 0;
			}
		}
	}
	

	if (player1team[player1Number].getAlive() == true)
	{
		player1footid = player1team[player1Number].getID();
	}
	if (player2team[player2Number].getAlive() == true)
	{
		player2footid = player2team[player2Number].getID();
	}
	system.update(Particleclock.restart());

	World.Step(1 / 60.f, 8, 3);
	if (captain1placed == true)
	{
		captain1.UpdateSprite();
	}
	if (capatain2placed == true)
	{
		captain2.UpdateSprite();
	}
	if (BuildMode == true)
	{
		turnCLock.restart().asSeconds();
	}

	soundManager.update(playerPosition, playerVelocity, sf::Vector2f(playerPosition.x, 555));
	water1.updateWater();
	water2.updateWater();
	water3.updateWater();

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
		checkAlive();
		turn.setString(std::to_string((int)turnTimer));
		if (Player1Turn == true)
		{

			turn.setPosition(player1team[player1Number].getPosition().x , player1team[player1Number].getPosition().y - 60);
			cross.Update(player1team[player1Number].getPosition(),player1team[player1Number].getType(),player1team[player1Number]);
			player1team[player1Number].Update(numFootContacts,World);
			playerVelocity = player1team[player1Number].getVelocity();
			playerPosition = player1team[player1Number].getPosition();
			turnTimer -= turnCLock.restart().asSeconds();
			game->window.setKeyRepeatEnabled(true);
			if (player1Fire == true)
			{
				if (player1team[player1Number].getType() == 2 && Handguns.size() == 0)
				{
					player1Fire == false;
				}
				else if (player1team[player1Number].getType() == 3 && Shotguns.size() == 0)
				{
					player1Fire == false;
				}
				else if (player1team[player1Number].getType() == 4 && Snipers.size() == 0)
				{
					player1Fire == false;
				}
			}
		}
		else
		{
			turn.setPosition(player2team[player2Number].getPosition().x , player2team[player2Number].getPosition().y - 60);
			turnTimer -= turnCLock.restart().asSeconds();
			game->window.setKeyRepeatEnabled(false);
			cross.Update(player2team[player2Number].getPosition(), player2team[player2Number].getType(), player1team[player1Number]);
			player2team[player2Number].Update(numFootContacts2,World);
			playerPosition = player2team[player2Number].getPosition();
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
	



	for (int i = 0; i < player1team.size(); i++)
	{
		game->window.draw(player1team[i].getSprite());
		sf::Text temp;
		temp.setFont(font);
		temp.setColor(sf::Color::Black);
		temp.setStyle(sf::Text::Bold);
		temp.setPosition(0, 0);
		temp.setCharacterSize(20);
		if (player1team[i].getAlive() == true)
		{

			temp.setString(player1team[i].getHealthText());
			temp.setPosition(player1team[i].getPosition().x - 10, player1team[i].getPosition().y - 40);
			game->window.draw(temp);
		}

	}
	for (int i = 0; i < player2team.size(); i++)
	{
		game->window.draw(player2team[i].getSprite());
		
		sf::Text temp;
		temp.setFont(font);
		temp.setColor(sf::Color::Black);
		temp.setStyle(sf::Text::Bold);
		temp.setPosition(0, 0);
		temp.setCharacterSize(20);
		if (player2team[i].getAlive() == true)
		{

			temp.setString(player2team[i].getHealthText());
			temp.setPosition(player2team[i].getPosition().x - 10, player2team[i].getPosition().y - 40);
			game->window.draw(temp);
		}
	}
	game->window.draw(captain1.getSprite());
	game->window.draw(captain2.getSprite());
	game->window.draw(cross.getSprite());
	game->window.draw(cross.getGunSprite());
	game->window.draw(boundingbox);
	water1.Draw(game);
	water2.Draw(game);
	water3.Draw(game);


	for (int i = 0; i < player1team.size(); i++)
	{
		player1team[i].UpdateSprite();
	}
	for (int i = 0; i < player2team.size(); i++)
	{
		player2team[i].UpdateSprite();
	}
	if (BuildMode == false)
	{
		captain2health.setPosition(captain2.getPosition().x - 10, captain2.getPosition().y - 40);
		captain2health.setString(captain2.getHealthText());
		captain1health.setString(captain1.getHealthText());
		captain1health.setPosition(captain1.getPosition().x - 10, captain1.getPosition().y - 40);
		game->window.draw(captain2health);
		game->window.draw(captain1health);
	}

	if (BuildMode == true)
	{

		for (int i = 0; i < player1team.size(); i++)
		{
			game->window.draw(player1team[i].getSprite());
		}
		for (int i = 0; i < player2team.size(); i++)
		{
			game->window.draw(player2team[i].getSprite());
		}
		game->window.draw(HudSprite);
		game->window.draw(RocketPlayerSprite);
		game->window.draw(shotgunplayersprite);
		game->window.draw(hangunplayersprite);
		game->window.draw(sniperplayersprite);
		game->window.draw(DirtBlockHud);
		game->window.draw(FinishButtonSprite);
		game->window.draw(currentPlayer);
		game->window.draw(Money);
		game->window.draw(dirtPriceText);
		game->window.draw(concreteblockhud);
		game->window.draw(steelblockhud);
		game->window.draw(HandgunPriceText);
		game->window.draw(ShotgunPriceText);
		game->window.draw(SniperPriceText);
		game->window.draw(concretepriceText);
		game->window.draw(steelpriceText);
		game->window.draw(dirtName);
		game->window.draw(steelName);
		game->window.draw(concreteName);
		game->window.draw(handgunName);
		game->window.draw(rocketName);
		game->window.draw(shotgunName);
		game->window.draw(sniperName);
		game->window.draw(RocketPlayerPriceText);
		game->window.draw(placingspriteCircle);
		if (PlaceBlockMode == true || PlacePlayerMode == true || captainplacemode == true)
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

//	DrawDebug();
	if (soundManager.getReverbActive() == true)
	{
	//	game->window.draw(reverbCircle);
	//	game->window.draw(reverbCircle2);
	}
	updateHandguns();
	updateShotguns();
	updateSnipers();
	game->window.draw(turn);
	game->window.display();
	AcitvateGameOverState();
	return;
}


void Play::updateHandguns(){

	for (int i = 0; i < Handguns.size(); i++)
	{
		Handguns[i].Update();
		for (int j = 0; j < blocks.size(); j++)
		{
			if (abs(Handguns[i].getPosition().x - blocks[j].getBody()->GetPosition().x *SCALE) < 50 && abs(Handguns[i].getPosition().y - blocks[j].getBody()->GetPosition().y*SCALE) < 50)
			{
				if (CollisionManager::CircleRectangleCollision(Handguns[i].getCircleCol(), blocks[j].getRect()) == true)
				{
					Handguns[i].setAlive(false);
					blocks[j].CheckLives();
				}							
			}		
		}
		if (CollisionManager::CircleRectangleCollision(Handguns[i].getCircleCol(), captain1.getPlayerRectangle()) == true)
		{
			Handguns[i].setAlive(false);
			captain1.setHealth(10);
		}
		else if (CollisionManager::CircleRectangleCollision(Handguns[i].getCircleCol(), captain2.getPlayerRectangle()) == true)
		{
			Handguns[i].setAlive(false);
			captain2.setHealth(10);
		}
			
		for (int k = 0; k < player2team.size(); k++)
		{
			if (CollisionManager::CircleRectangleCollision(Handguns[i].getCircleCol(), player2team[k].getPlayerRectangle()) == true)
			{
				Handguns[i].setAlive(false);
				player2team[k].setHealth(15);
			}
		}
		for (int l = 0; l < player1team.size(); l++)
		{
			if (CollisionManager::CircleRectangleCollision(Handguns[i].getCircleCol(), player1team[l].getPlayerRectangle()) == true)
			{
				Handguns[i].setAlive(false);
				player1team[l].setHealth(15);
			}
		}
		game->window.draw(Handguns[i].getSprite());
	//	game->window.draw(Handguns[i].getCircleCol());
		if (Handguns[i].getAlive() == false)
		{
			lastbulletpos = Handguns[i].getPosition();
			bullerTimer = 1.5f;
			CountDown = true;
			Handguns.pop_back();
			SwitchTurn();
		}
	}
}
void Play::updateSnipers()
{
	for (int i = 0; i < Snipers.size(); i++)
	{

		Snipers[i].Update();

		for (int j = 0; j < blocks.size(); j++)
		{
			if (abs(Snipers[i].getPosition().x - blocks[j].getBody()->GetPosition().x *SCALE) < 50 && abs(Snipers[i].getPosition().y - blocks[j].getBody()->GetPosition().y*SCALE) < 50)
			{
				if (CollisionManager::CircleRectangleCollision(Snipers[i].getCircleCol(), blocks[j].getRect()) == true)
				{
					Snipers[i].setAlive(false);
					blocks[j].CheckLives();
				}
			}
		}
		if (CollisionManager::CircleRectangleCollision(Snipers[i].getCircleCol(), captain1.getPlayerRectangle()) == true)
		{
			Snipers[i].setAlive(false);
			captain1.setHealth(50);

		}
		else if (CollisionManager::CircleRectangleCollision(Snipers[i].getCircleCol(), captain2.getPlayerRectangle()) == true)
		{
			Snipers[i].setAlive(false);
			captain2.setHealth(50);
		}
		for (int k = 0; k < player2team.size(); k++)
		{
			if (CollisionManager::CircleRectangleCollision(Snipers[i].getCircleCol(), player2team[k].getPlayerRectangle()) == true)
			{
				Snipers[i].setAlive(false);
				player2team[k].setHealth(50);
			}
		}
		for (int l = 0; l < player1team.size(); l++)
		{
			if (CollisionManager::CircleRectangleCollision(Snipers[i].getCircleCol(), player1team[l].getPlayerRectangle()) == true)
			{
				Snipers[i].setAlive(false);
				player1team[l].setHealth(50);
			}
		}
		game->window.draw(Snipers[i].getSprite());
		//game->window.draw(Shotguns[i].getCircleCol());
		if (Snipers[i].getAlive() == false)
		{
			lastbulletpos = Snipers[i].getPosition();
			bullerTimer = 1.5f;
			CountDown = true;
			Snipers.pop_back();
			SwitchTurn();
		}
	}
}
void Play::updateShotguns()
{
	for (int i = 0; i < Shotguns.size(); i++)
	{
		Shotguns[i].Update();
		for (int j = 0; j < blocks.size(); j++)
		{
			if (abs(Shotguns[i].getPosition().x - blocks[j].getBody()->GetPosition().x *SCALE) < 50 && abs(Shotguns[i].getPosition().y - blocks[j].getBody()->GetPosition().y*SCALE) < 50)
			{
				if (CollisionManager::CircleRectangleCollision(Shotguns[i].getCircleCol(), blocks[j].getRect()) == true)
				{
					Shotguns[i].setAlive(false);
					blocks[j].CheckLives();
				}
			}
		}
		if (CollisionManager::CircleRectangleCollision(Shotguns[i].getCircleCol(), captain1.getPlayerRectangle()) == true)
		{
			Shotguns[i].setAlive(false);
			captain1.setHealth(30);
		}
		else if (CollisionManager::CircleRectangleCollision(Shotguns[i].getCircleCol(), captain2.getPlayerRectangle()) == true)
		{
			Shotguns[i].setAlive(false);
			captain2.setHealth(30);
		}
		for (int k = 0; k < player2team.size(); k++)
		{
			if (CollisionManager::CircleRectangleCollision(Shotguns[i].getCircleCol(), player2team[k].getPlayerRectangle()) == true)
			{
				Shotguns[i].setAlive(false);
				player2team[k].setHealth(5);
			}
		}
		for (int l = 0; l < player1team.size(); l++)
		{
			if (CollisionManager::CircleRectangleCollision(Shotguns[i].getCircleCol(), player1team[l].getPlayerRectangle()) == true)
			{
				Shotguns[i].setAlive(false);
				player1team[l].setHealth(5);
			}
		}
		game->window.draw(Shotguns[i].getSprite());
		//game->window.draw(Shotguns[i].getCircleCol());
		if (Shotguns[i].getAlive() == false)
		{
			lastbulletpos = Shotguns[i].getPosition();
			bullerTimer = 1.5f;
			CountDown = true;
			Shotguns.pop_back();
			SwitchTurn();
			zoomed = false;
		}
	}
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
						if (Player1Turn == true )
						{
							if (CountDown == false)
							{
								if (player1team[player1Number].getType() == 1 && Rockets.size() == 0)
								{
									player1Fire = true;
									Rocket tempRocket(World, cross.getPosition(), RocketTexture, player1team[player1Number].getPosition());
									Rockets.push_back(tempRocket);
									if (effectToggle == true)
									{
										soundManager.playFireSound();
									}
									InitRocketParticle();
								}
								else if (player1team[player1Number].getType() == 2 && Handguns.size() == 0)
								{
									player1Fire = true;
									Handgun temp( HandgunBulletTexture, cross.getPosition(), player1team[player1Number].getPosition());
									Handguns.push_back(temp);							
								}
								else if (player1team[player1Number].getType() ==  3 && Shotguns.size()==0)
								{
									player1Fire = true;
									Shotgun tempTop(shotgunBulletTex, cross.getPosition(), player1team[player1Number].getPosition(),0.5f);
									Shotgun tempTop1(shotgunBulletTex, cross.getPosition(), player1team[player1Number].getPosition(), 0.25f);
									Shotgun temp(shotgunBulletTex, cross.getPosition(), player1team[player1Number].getPosition(), 0);
									Shotgun tempBottom1(shotgunBulletTex, cross.getPosition(), player1team[player1Number].getPosition(), -0.25f);
									Shotgun tempBottom(shotgunBulletTex, cross.getPosition(), player1team[player1Number].getPosition(), -0.5f);
									Shotguns.push_back(tempTop);
									Shotguns.push_back(temp);
									Shotguns.push_back(tempBottom);
									Shotguns.push_back(tempBottom1);
									Shotguns.push_back(tempTop1);
								}
								else if (player1team[player1Number].getType() == 4 && Snipers.size() ==0)
								{
									player1Fire = true;
									Sniper temp(sniperBullettex, cross.getPosition(), player1team[player1Number].getPosition());
									Snipers.push_back(temp);
								}
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
								if (player2team[player2Number].getType() == 1 && Rockets.size() ==0)
								{

									player2Fire = true;
									Rocket tempRocket(World, cross.getPosition(), RocketTexture, player2team[player2Number].getPosition());
									Rockets.push_back(tempRocket);
									if (effectToggle == true)
									{
										soundManager.playFireSound();
									}
									InitRocketParticle();
								}
								else if (player2team[player2Number].getType() == 2 && Handguns.size() == 0)
								{
									player2Fire = true;
									Handgun temp(HandgunBulletTexture, cross.getPosition(), player2team[player2Number].getPosition());
									Handguns.push_back(temp);		
								}
								else if (player2team[player2Number].getType() == 3 && Shotguns.size()==0)
								{
									player2Fire = true;
									Shotgun tempTop(shotgunBulletTex, cross.getPosition(), player2team[player2Number].getPosition(), 0.5f);
									Shotgun tempTop1(shotgunBulletTex, cross.getPosition(), player2team[player2Number].getPosition(), 0.25f);
									Shotgun temp(shotgunBulletTex, cross.getPosition(), player2team[player2Number].getPosition(), 0);
									Shotgun tempBottom(shotgunBulletTex, cross.getPosition(), player2team[player2Number].getPosition(), -0.5f);
									Shotgun tempBottom1(shotgunBulletTex, cross.getPosition(), player2team[player2Number].getPosition(), -0.25f);
									Shotguns.push_back(tempTop);
									Shotguns.push_back(temp);
									Shotguns.push_back(tempBottom);
									Shotguns.push_back(tempBottom1);
									Shotguns.push_back(tempTop1);

								}
								else if (player2team[player2Number].getType() == 4 && Snipers.size() == 0)
								{
									player1Fire = true;
									Sniper temp(sniperBullettex, cross.getPosition(), player2team[player2Number].getPosition());
									Snipers.push_back(temp);
								}
								//soundManager.PlayRocket();
								overview = false;
							}
							//soundManager.PlayRocket();
							//RocketFired = true;
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
			if (buildViewenter.x > 390)
			{
				if (event.key.code == sf::Keyboard::Left && BuildMode == true)
				{
					buildViewenter.x -= 20;
					HudSpritePosition.x -= 20;
				}
			}
			if (buildViewenter.x < 1590)
			{
				if (event.key.code == sf::Keyboard::Right && BuildMode == true)
				{
					buildViewenter.x += 20;
					HudSpritePosition.x += 20;
				}
			}
			if (buildViewenter.y > -100)
			{
				if (event.key.code == sf::Keyboard::Up && BuildMode == true)
				{
					buildViewenter.y -= 20;
					HudSpritePosition.y -= 20;
				}
			}
			if (buildViewenter.y < 600)
			{
				if (event.key.code == sf::Keyboard::Down && BuildMode == true)
				{
					buildViewenter.y += 20;
					HudSpritePosition.y += 20;
				}
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
			else if (BodyIterator->GetUserData() == "concrete"){
				sf::Sprite Sprite;
				Sprite.setTexture(concreteblock);
				Sprite.setOrigin(10, 10);
				Sprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				Sprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(Sprite);
				++BodyCount;
			}
			else if (BodyIterator->GetUserData() == "steel"){
				sf::Sprite Sprite;
				Sprite.setTexture(steelblock);
				Sprite.setOrigin(10, 10);
				Sprite.setPosition(BodyIterator->GetPosition().x*SCALE, BodyIterator->GetPosition().y*SCALE);
				Sprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
				game->window.draw(Sprite);
				++BodyCount;
			}
		}


	}
}

void Play::SwitchTurn()
{
	numFootContacts = 2;
	numFootContacts2 = 2;

	

	if (Player1Turn == true  )
	{

		player1Fire = false;	
		overview = false;
		turnTimer = 15;
		if (player2teamdead == false)
		{
			Player1Turn = false;
		}

		if ((player1Number + 1) < player1team.size())
		{
			player1Number++;

		}
		else if ((player1Number +1) == player1team.size())
		{
			player1Number =0;
		}
	}

	else if (Player1Turn == false)
	{
		player2Fire = false;
		overview = false;
		turnTimer = 15;
		if (player1teamdead == false)
		{
			Player1Turn = true;
		}

		if ((player2Number + 1) < player2team.size())
		{
			player2Number++;

		}
		else if ((player2Number + 1) == player2team.size())
		{
			player2Number = 0;
		}
	
	}




}

void Play::CreatePlayer(sf::Vector2f pos, int team,int type)
{
	Player temp;
	if (team == 1)
	{
		temp = Player(numberPlayersTeam1 + 1, World, pos, playerTexture, 1, type);
		player1team.push_back(temp);
	}
	else if (team == 2)
	{
		temp = Player(numberPlayersTeam2 + 1, World, pos, player2Texture, 2, type);
		player2team.push_back(temp);
	}


	numberPlayersTeam1 = player1team.size();
	numberPlayersTeam2 = player2team.size();
	
	
}
void Play::CreateCaptain(sf::Vector2f pos, int team, int type)
{
	
	if (team == 1)
	{
		captain1= Player(1000,World, pos, captainTexture1, 3, type);
	
	}
	else if (team == 2)
	{
		captain2 = Player(1001,World, pos, captaintexture2, 4, type);
	}

}

void Play::BuildModeUpdate(){

	
	HudSprite.setPosition(HudSpritePosition);
	FinishButtonSprite.setPosition(HudSpritePosition + sf::Vector2f(350, 100));
	PlaceCaptaintext.setPosition(HudSpritePosition + sf::Vector2f(70, -300));
	sf::Vector2i windowPosition = sf::Vector2i(buildView.getCenter().x - 400, buildView.getCenter().y - 300);
	sf::Vector2i position = sf::Mouse::getPosition(game->window) + windowPosition;


	DirtBlockHud.setPosition(HudSpritePosition + sf::Vector2f(90, 60));
	dirtPriceText.setPosition(DirtBlockHud.getPosition() + sf::Vector2f(0, 20));
	dirtName.setPosition(DirtBlockHud.getPosition() + sf::Vector2f(-10, -25));

	concreteblockhud.setPosition(HudSpritePosition + sf::Vector2f(160, 60));
	concretepriceText.setPosition(concreteblockhud.getPosition() + sf::Vector2f(0, 20));
	concreteName.setPosition(concreteblockhud.getPosition() + sf::Vector2f(-30, -25));

	steelblockhud.setPosition(HudSpritePosition + sf::Vector2f(230, 60));
	steelpriceText.setPosition(steelblockhud.getPosition() + sf::Vector2f(0, 20));
	steelName.setPosition(steelblockhud.getPosition() + sf::Vector2f(-10, -25));

	RocketPlayerSprite.setPosition(HudSpritePosition + sf::Vector2f(450, 60));
	RocketPlayerPriceText.setPosition(RocketPlayerSprite.getPosition() + sf::Vector2f(0, 30));
	rocketName.setPosition(RocketPlayerSprite.getPosition() + sf::Vector2f(-20, -20));

	hangunplayersprite.setPosition(HudSpritePosition + sf::Vector2f(550, 60));
	HandgunPriceText.setPosition(hangunplayersprite.getPosition() + sf::Vector2f(0, 30));
	handgunName.setPosition(hangunplayersprite.getPosition() + sf::Vector2f(-20, -20));

	shotgunplayersprite.setPosition(HudSpritePosition + sf::Vector2f(650, 60));
	ShotgunPriceText.setPosition(shotgunplayersprite.getPosition() + sf::Vector2f(0, 30));
	shotgunName.setPosition(shotgunplayersprite.getPosition() + sf::Vector2f(-20, -20));

	sniperplayersprite.setPosition(HudSpritePosition + sf::Vector2f(750, 60));
	SniperPriceText.setPosition(sniperplayersprite.getPosition() + sf::Vector2f(0, 30));
	sniperName.setPosition(sniperplayersprite.getPosition() + sf::Vector2f(-20, -20));
	

	if (Player1Turn == true)
	{

		RocketPlayerSprite.setTexture(RocketPlayerTexture);
		hangunplayersprite.setTexture(handgunplayer1);
		shotgunplayersprite.setTexture(shotgunplayer1);
		sniperplayersprite.setTexture(sniperplayer1);
		currentPlayer.setString("PLAYER 1,  ");
		currentPlayer.setPosition(HudSpritePosition + sf::Vector2f(210, 10));
		Money.setString(" Credits Remaining = " + std::to_string(CurrentPlayer1Money));
		Money.setPosition(HudSpritePosition + sf::Vector2f(310, 10));
		PlaceCaptaintext.setString("PLAYER 1 PLACE YOUR CAPTAIN!!");


	}
	else if (Player1Turn == false)
	{
		RocketPlayerSprite.setTexture(RocketPlayerTexture2);
		hangunplayersprite.setTexture(handgunplayer2);
		shotgunplayersprite.setTexture(shotgunplayer2);
		sniperplayersprite.setTexture(sniperplayer2);
		currentPlayer.setString("PLAYER 2, ");
		currentPlayer.setPosition(HudSpritePosition + sf::Vector2f(210, 10));
		Money.setString(" Credits Remaining = " +std::to_string(CurrentPlayer2Money));
		Money.setPosition(HudSpritePosition + sf::Vector2f(310, 10));
		PlaceCaptaintext.setString("PLAYER 2 PLACE YOUR CAPTAIN!!");
	}
	
	if (captainplacemode == true)
	{
		game->window.draw(PlaceCaptaintext);
		if (Player1Turn == true)
		{
			placingSprite.setTexture(captainTexture1);
		}
		else
		{
			placingSprite.setTexture(captaintexture2);
		}
	
	
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousereleased == true && placeable == true)
		{
			
			if (Player1Turn == true && placingSprite.getPosition().x < 990)
			{
			
				mousereleased = false;
				captain1placed = true;
				CreateCaptain(sf::Vector2f(position.x, position.y), 1, playerType);
				Player1Turn = false;
				
			}
			else if (Player1Turn == false  && placingSprite.getPosition().x > 990)
			{

				mousereleased = false;
				capatain2placed = true;
				CreateCaptain(sf::Vector2f(position.x, position.y), 2, playerType);
				captainplacemode = false;
				Player1Turn = true;
			}
			
		}

		placingSprite.setPosition(sf::Vector2f(position.x - 10, position.y - 10));
	}

	if (PlaceBlockMode == true)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mousereleased == true)
		{
			PlaceBlockMode = false;
		}

		if (currentType == 8)
		{
			blockSprite.setTexture(dirttex);
			placingSprite = blockSprite;
			price = dirtprice;
		}
		if (currentType == 10)
		{
			blockSprite.setTexture(concreteblock);
			placingSprite = blockSprite;
			price = concretePrice;
		}
		if (currentType == 11)
		{
			blockSprite.setTexture(steelblock);
			placingSprite = blockSprite;
			price = steelPrice;
		}

		placingSprite.setPosition(sf::Vector2f(position.x - 10, position.y - 10));



		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousereleased == true && placeable == true)
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



	if (PlacePlayerMode == true)//////////////////////////////////////////////////////////////////////////////////
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && mousereleased == true && placeable == true)
		{
			PlacePlayerMode = false;
		}

		if (playerType == 1)
		{
			if (Player1Turn == true)
			{
				RocketPlayerSprite.setTexture(RocketPlayerTexture);
				placingSprite = RocketPlayerSprite;
					
			}
			else 
			{	
				RocketPlayerSprite.setTexture(RocketPlayerTexture2);
				placingSprite = RocketPlayerSprite;
			}	
			price = rocketPrice;
		}
		else if (playerType == 2)
		{
			if (Player1Turn == true )
			{
				hangunplayersprite.setTexture(handgunplayer1);
				placingSprite = hangunplayersprite;

			}
			else 
			{

				hangunplayersprite.setTexture(handgunplayer2);
				placingSprite = hangunplayersprite;

			}


			price = handgunPrice;
		}
		else if (playerType == 3)
		{
			if (Player1Turn == true )
			{
				shotgunplayersprite.setTexture(shotgunplayer1);
				placingSprite = shotgunplayersprite;

			}
			else 
			{

				shotgunplayersprite.setTexture(shotgunplayer2);
				placingSprite = shotgunplayersprite;

			}


			price = shotgunPrice;
		}
		else if (playerType == 4)
		{
			if (Player1Turn == true )
			{
				sniperplayersprite.setTexture(sniperplayer1);
				placingSprite = sniperplayersprite;

			}
			else 
			{

				sniperplayersprite.setTexture(sniperplayer2);
				placingSprite = sniperplayersprite;

			}


			price = sniperPrice;
		}

		placingSprite.setPosition(sf::Vector2f(position.x - 10, position.y - 10));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousereleased == true)
		{
			if (Player1Turn == true && CurrentPlayer1Money >= price && placingSprite.getPosition().x < 990)
			{
				mousereleased = false;
				CreatePlayer(sf::Vector2f(position.x, position.y), 1, playerType);
				CurrentPlayer1Money -= price;
			}
			else if (Player1Turn == false && CurrentPlayer2Money >= price && placingSprite.getPosition().x > 990)
			{
				mousereleased = false;
				CreatePlayer(sf::Vector2f(position.x, position.y), 2, playerType);
				CurrentPlayer2Money -= price;
			}
		}
	}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousereleased == true)
		{
			mousereleased = false;
			if (CheckClicked(DirtBlockHud, position) == true)
			{		
					currentType = 8;
					PlaceBlockMode = true;		
			}
			if (CheckClicked(concreteblockhud, position) == true)
			{		
					currentType = 10;
					PlaceBlockMode = true;	
			}
			if (CheckClicked(steelblockhud, position) == true)
			{
				currentType = 11;
				PlaceBlockMode = true;
			}

			else if (CheckClicked(FinishButtonSprite, position) == true)
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
			else if (CheckClicked(RocketPlayerSprite, position) == true)
			{
				playerType = 1;
				PlacePlayerMode = true;
			}
			else if (CheckClicked(hangunplayersprite, position) == true)
			{
				playerType = 2;
				PlacePlayerMode = true;
			}
			else if (CheckClicked(shotgunplayersprite, position) == true)
			{
				playerType = 3;
				PlacePlayerMode = true;
			}
			else if (CheckClicked(sniperplayersprite, position) == true)
			{
				playerType = 4;
				PlacePlayerMode = true;
			}

		}	
}
void Play::GameStart()
{
	
	BuildMode = false;
	
	Player1Turn = true;

	captain1health.setFont(font);
	captain1health.setStyle(sf::Text::Bold);
	captain1health.setPosition(0, 0);
	captain1health.setCharacterSize(20);
	captain1health.setColor(sf::Color::Black);
	captain2health.setFont(font);
	captain2health.setFont(font);
	captain2health.setStyle(sf::Text::Bold);
	captain2health.setPosition(0, 0);
	captain2health.setCharacterSize(20);
	captain2health.setColor(sf::Color::Black);

	player2health.setFont(font);
	player2health.setStyle(sf::Text::Bold);
	player2health.setPosition(0, 0);
	player2health.setCharacterSize(20);
	player2health.setColor(sf::Color::Black);

	cross.Init(CrosshairTexture, position,handguntex,rocketlaunchertex,shotguntex,snipertex);


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
			if (player1team[player1Number].getType() == 1)
			{
				for (int i = 0; i < Rockets.size(); i++)
				{
					if (player1Fire == true && overview == false)
					{
						if (Rockets[i].getPosition().x < bulletOffset)
						{
							bulletView.setCenter(bulletOffset, Rockets[i].getPosition().y);
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
						if (Rockets[i].getPosition().x > bulletOffset &&  Rockets[i].getPosition().x < gameSize - bulletOffset)
						{
							bulletView.setCenter(sf::Vector2f(Rockets[i].getPosition()));
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
						if (Rockets[i].getPosition().x > gameSize - bulletOffset)
						{

							bulletView.setCenter(gameSize - bulletOffset, Rockets[i].getPosition().y);
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
					}
				}
			}
			else if (player1team[player1Number].getType() == 4)
			{
				for (int i = 0; i < Snipers.size(); i++)
				{
					if (player1Fire == true && overview == false)
					{
						if (Snipers[i].getPosition().x < bulletOffset)
						{
							bulletView.setCenter(bulletOffset, Snipers[i].getPosition().y);
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
						if (Snipers[i].getPosition().x > bulletOffset &&  Snipers[i].getPosition().x < gameSize - bulletOffset)
						{
							bulletView.setCenter(sf::Vector2f(Snipers[i].getPosition()));
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
						if (Snipers[i].getPosition().x > gameSize - bulletOffset)
						{

							bulletView.setCenter(gameSize - bulletOffset, Snipers[i].getPosition().y);
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
					}
				}
			}
		}
		else if (Player1Turn == false && overview == false)
		{
			game->window.setView(player2View);
			if (player2team[player2Number].getType() == 1)
			{
				for (int i = 0; i < Rockets.size(); i++)
				{
					if (player2Fire == true && overview == false)
					{

						if (Rockets[i].getPosition().x < bulletOffset)
						{
							bulletView.setCenter(bulletOffset, Rockets[i].getPosition().y);
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
						if (Rockets[i].getPosition().x > bulletOffset &&  Rockets[i].getPosition().x < gameSize - bulletOffset)
						{
							bulletView.setCenter(sf::Vector2f(Rockets[i].getPosition()));
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
						if (Rockets[i].getPosition().x > gameSize - bulletOffset)
						{

							bulletView.setCenter(gameSize - bulletOffset, Rockets[i].getPosition().y);
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
					}
				}
			}
			else if (player2team[player2Number].getType() == 4)
			{
				for (int i = 0; i < Snipers.size(); i++)
				{
					if (player1Fire == true && overview == false)
					{
						if (Snipers[i].getPosition().x < bulletOffset)
						{
							bulletView.setCenter(bulletOffset, Snipers[i].getPosition().y);
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
						if (Snipers[i].getPosition().x > bulletOffset &&  Snipers[i].getPosition().x < gameSize - bulletOffset)
						{
							bulletView.setCenter(sf::Vector2f(Snipers[i].getPosition()));
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
						if (Snipers[i].getPosition().x > gameSize - bulletOffset)
						{

							bulletView.setCenter(gameSize - bulletOffset, Snipers[i].getPosition().y);
							bulletView.setSize(900, 675);
							game->window.setView(bulletView);
						}
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

		for (int j = 0; j < blocks.size(); j++)
		{
			if (abs(Rockets[i].getPosition().x - blocks[j].getBody()->GetPosition().x *SCALE) < 50 && abs(Rockets[i].getPosition().y - blocks[j].getBody()->GetPosition().y*SCALE) < 50)
			{
				if (CollisionManager::CircleRectangleCollision(Rockets[i].getCircle(), blocks[j].getRect()) == true)
				{
					destroyRocket = true;
					Groundhit = true;
					
				}
			}
		}
		if (CollisionManager::CircleRectangleCollision(Rockets[i].getCircle(), captain1.getPlayerRectangle()) == true)
		{
			destroyRocket = true;
			captain1.setHealth(50);

		}
		else if (CollisionManager::CircleRectangleCollision(Rockets[i].getCircle(), captain2.getPlayerRectangle()) == true)
		{
			destroyRocket = true;
			captain2.setHealth(50);
		}
		
		for (int k = 0; k < player2team.size(); k++)
		{

			if (CollisionManager::CircleRectangleCollision(Rockets[i].getCircle(), player2team[k].getPlayerRectangle()) == true)
			{
				destroyRocket = true;
				Groundhit = true;
			}
		}
		for (int k = 0; k < player1team.size(); k++)
		{

			if (CollisionManager::CircleRectangleCollision(Rockets[i].getCircle(), player1team[k].getPlayerRectangle()) == true)
			{
				destroyRocket = true;
				Groundhit = true;
			}
		}

		Rockets[i].Update(World);
	/*	game->window.draw(Rockets[i].getCircle());*/
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
void Play::checkAlive(){

	
	for (int i = 0; i < player1team.size(); i++)
	{
		if (player1team[i].getHealth() <= 0 || player1team[i].getPosition().y > 700)
		{
			player1team[i].setAlive(false);
			player1team[i].DestoryBody();
		
		}
	}

	for (int i = 0; i < player2team.size(); i++)
	{
		if (player2team[i].getHealth() <= 0 )
		{
			player2team[i].setAlive(false);
			player2team[i].DestoryBody();
	
		}
	}
}
void Play::UpdateHealth()
{
	
	if (captain1hit == true)
	{
		captain1.setHealth(20);
		captain1hit = false;
	}
	if (captain2hit == true)
	{
		captain2.setHealth(20);
		captain2hit = false;
	}

	captain1health.setPosition(captain1.getPosition().x - 10, captain1.getPosition().y- 40);
	captain1health.setString(std::to_string(captain1.getHealth()));
	captain2health.setPosition(captain2.getPosition().x - 10, captain2.getPosition().y - 40);
	captain2health.setString(std::to_string(captain2.getHealth()));


	if (captain1.getHealth() <= 0 || captain1.getPosition().y > 900)
	{    
		//game->pushState(new GameOver(this->game,"Player 2 Wins"));
		changeState = true;
	}
	else if (captain2.getHealth() <= 0 || captain2.getPosition().y > 900)
	{
	//	game->pushState(new GameOver(this->game, "Player 1 Wins"));
		changeState = true;
	}
	else if (player1teamdead == true && player2teamdead == true)
	{
		
	//	game->pushState(new GameOver(this->game, "This game is a tie!"));
		changeState = true;
	}
	

	
}

Play::~Play(){


}
void Play::AcitvateGameOverState(){

	if (changeState == true)
	{
		//for (int i = 0; i < blocks.size(); i++)
		//{
		//	if (World.IsLocked() == false)
		//	{
		//		World.DestroyBody(blocks[i].getBody());
		//		blocks.erase(blocks.begin() + i);
		//		//		std::vector<Block>::iterator newEnd = std::remove(blocks.begin(), blocks.end(), i);
		//	}
		//}
	//	World.~b2World();
		game->changeState(new GameOver(this->game,""));
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
		boundingbox.setPosition(sf::Vector2f(lastbulletpos.x - boundingbox.getRadius() , lastbulletpos.y-boundingbox.getRadius()));
		for (int i = 0; i < blocks.size(); i++)
		{
			if (CollisionManager::CircleDetectCollision(boundingbox,blocks[i].getCircle()) == true)
			{
				blocks[i].CheckLives();
			}
		}
		for (int j = 0; j < player1team.size(); j++)
		{
			if (CollisionManager::CircleRectangleCollision(boundingbox,player1team[j].getPlayerRectangle()) == true)
			{
				player1team[j].setHealth(50);
			}
		}
		for (int j = 0; j < player2team.size(); j++)
		{
			if (CollisionManager::CircleRectangleCollision(boundingbox, player2team[j].getPlayerRectangle()) == true)
			{
				player2team[j].setHealth(50);
			}
		}

		boundingbox.setPosition(-500, -500);
		Groundhit = false;
	}
}



