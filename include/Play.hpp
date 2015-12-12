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
	

	sf::Texture Snowtexture;
	thor::ParticleSystem system;
	sf::Clock Particleclock;
	thor::UniversalEmitter Snowemitter1;
	thor::UniversalEmitter Snowemitter2;
	thor::UniversalEmitter Snowemitter3;

	sf::Clock RocketParticleclock;
	sf::Texture Firetexture;
	thor::ParticleSystem Rocketsystem;
	thor::UniversalEmitter RocketEmitter;

	int bulletOffset;
	SoundManager soundManager;
	sf::Vector2f position;
	sf::Font font;
    int wormcount;
	/** Prepare the world */
	bool Player1Turn;
	sf::Vector2f playerVelocity;
	sf::Vector2f playerPosition;
	bool RocketFired;
	bool BuildMode;
	bool PlaceMode;
	bool mousereleased;
	sf::Sprite placingSprite;
	sf::Text player1health;
	sf::Text player2health;
	Water water1, water2, water3;
	vector<Block> blocks;
	int currentType;
	//sf::Texture grasstexture;
	sf::Texture backGroundTexture;
	sf::Texture playerTexture;
	sf::Texture player2Texture;
	//sf::Texture DirtTexture;
	sf::Texture CrosshairTexture;
	sf::Texture Explosion;
	sf::Vector2f Explosionsource = sf::Vector2f(0, 0);
	sf::Sprite ExplosionSprite;
	sf::Texture FinishButtonTexture;
	sf::Sprite FinishButtonSprite;
	sf::Texture RocketTexture;
	sf::Texture dirttex;	
	sf::Texture topStraighttex;
	sf::Texture leftStraighttex;
	sf::Texture topLeftCornertex;
	sf::Texture topRightCornertex;
	sf::Texture bottomRightCornertex;
	sf::Texture rightStraight;
	sf::Texture bottomStraight;
	sf::Texture bottomLeftCorner;
	sf::Texture hudPanelTex;
	sf::Vector2f cameraposition;
	sf::View player1View, player2View, bulletView, buildView, standardView;
	int sizeofmap;
	bool outOfBounds;
	sf::Vector2f buildViewenter;
	
	Player player1;
	Player player2;

	Crosshair cross;
	bool player1Fire;
	bool player2Fire;
	std::vector<Rocket> Rockets;
	sf::Sprite background;
	int gameSize;
	int blockAmount;
	int blockWidth;
	int offset;
	sf::CircleShape  boundingbox;
	sf::Clock clock;
	float bullerTimer;
	bool CountDown;
	 int width=200;
	 int heigh30;
	 bool overview;
	 bool zoomed;
	 ///Hud Variables
	 sf::Sprite DirtBlockHud;
	 sf::Vector2f DirtBlockPosition;
	 sf::Sprite HudSprite;
	 sf::Vector2f HudSpritePosition;
	 sf::Text currentPlayer;
	 sf::Text Money;
	 sf::Text dirtPrice;
	 bool startExplosion;
	 int price;
	 int CurrentPlayer1Money;
	 int CurrentPlayer2Money;
	 float explosiontimer;

public:

	virtual void draw();
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
	void InitRocketParticle();
	void UpdateRocketParticle();
	bool CheckClicked(sf::Sprite sprite, sf::Vector2i position);
	void CreateBlock(int type, sf::Vector2i position);
	Play(Game* game);
};

#endif /* GAME_STATE_EDITOR_HPP */