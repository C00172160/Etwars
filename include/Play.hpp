#ifndef PLAY_HPP
#define PLAY_HPP

#include <SFML/Graphics.hpp>
#include "game_state.hpp"
#include "Thor\Particles\Particle.hpp"
#include "Thor\Particles\Affectors.hpp"
#include "Thor\Particles\EmissionInterface.hpp"
#include "Thor\Particles\Emitters.hpp"
#include "Thor\Particles\ParticleSystem.hpp"
#include "Thor\Particles.hpp"
#include "Thor\Vectors\VectorAlgebra3D.hpp"
#include "Thor\Math\Distributions.hpp"
#include "SFML\OpenGL.hpp"

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
#include "Water.h"
#include <math.h>
#include "SoundManager.h"
#include "SFMLDebugDraw.h"
#include "Menu.hpp"
#include "GameOver.hpp"

using namespace std;


class Play : public GameState
{
private:
	

	
	sf::Text turn;
	sf::Clock turnCLock;
	double turnTimer;

	sf::Texture Snowtexture;
	thor::ParticleSystem system;
	sf::Clock Particleclock;
	thor::UniversalEmitter Snowemitter1;
	thor::UniversalEmitter Snowemitter2;
	thor::UniversalEmitter Snowemitter3;
	sf::Texture captainTexture1 ,captaintexture2;
	sf::Clock RocketParticleclock;
	sf::Texture Firetexture;
	thor::ParticleSystem Rocketsystem;
	thor::UniversalEmitter RocketEmitter;
	vector<Player> player1team;
	vector<Player> player2team;
	int player1Number,player2Number,bulletOffset;
	SoundManager soundManager;
	sf::Vector2f position;
	sf::Font font;

	/** Prepare the world */

	sf::Vector2f playerVelocity;
	sf::Vector2f playerPosition;
	bool RocketFired, BuildMode, PlaceBlockMode, PlacePlayerMode, mousereleased, captainplacemode, Player1Turn, outOfBounds, player1Fire, player2Fire, sizeofmap,
	startExplosion, zoomed, CountDown, overview, players1Teamselected, players2TeamSeleced, effectToggle, reverbToggle, spacialToggle, backgroundToggle, waveToggle, 
	DopplerToggle;
	sf::Sprite placingSprite;
	sf::Text player1health, captain1health, captain2health, player2health;
	Water water1, water2, water3;
	vector<Block> blocks;
	int currentType;
	int playerType;
	
	//sf::Texture grasstexture;
	
	//sf::Texture DirtTexture;
	
	sf::Vector2f Explosionsource = sf::Vector2f(0, 0);
	sf::Sprite ExplosionSprite, FinishButtonSprite;
	sf::Texture RocketTexture,FinishButtonTexture,dirttex,topStraighttex,leftStraighttex,topLeftCornertex,topRightCornertex,
	bottomRightCornertex,rightStraight,bottomStraight,bottomLeftCorner,hudPanelTex,cameraposition,RocketPlayerTexture,backGroundTexture,
	playerTexture, player2Texture, CrosshairTexture, Explosion;

	sf::View player1View, player2View, bulletView, buildView, standardView;

	
	sf::Vector2f buildViewenter;
	
	Player player1, player2, captain1, captain2;

	Crosshair cross;
	 
	std::vector<Rocket> Rockets;
	sf::Sprite background;
	int gameSize, blockAmount, blockWidth, offset, price, CurrentPlayer1Money, CurrentPlayer2Money;
	sf::CircleShape  boundingbox;
	sf::Clock clock;
	float bullerTimer;

	 int width=200;
	 int heigh30;
	
	
	 ///Hud Variables
	 sf::Sprite DirtBlockHud;
	 sf::Vector2f DirtBlockPosition;
	 sf::Sprite HudSprite;
	 sf::Vector2f HudSpritePosition;
	 sf::Sprite RocketPlayerSprite;
	 sf::Vector2f RocketPlayerSpritePosition;
	 sf::Text currentPlayer, Money, dirtPrice, RocketPlayerPrice;
	 bool captain1placed, capatain2placed;
	 
	 float explosiontimer;
	 sf::CircleShape reverbCircle, reverbCircle2;

public:

	virtual void draw();
	void CreateCaptain(sf::Vector2f pos, int team, int type);
	void DrawDebug();
	virtual void update();
	virtual void handleInput();
	void PlayExplosion();
	void UpdateStaticBodies();
	void SwitchTurn();
	void UpdateCamera();
	void UpdateRockets();
	void UpdateHealth();
	void UpdateBlocks();
	void UpdateWater();
	void BuildModeUpdate();
	void GameStart();
	void CreatePlayer(sf::Vector2f pos, int team,int type);
	void InitRocketParticle();
	void UpdateRocketParticle();
	bool CheckClicked(sf::Sprite sprite, sf::Vector2i position);
	void CreateBlock(int type, sf::Vector2i position);
	Play(Game* game);
};

#endif /* GAME_STATE_EDITOR_HPP */