#ifndef PLAY_HPP
#define PLAY_HPP

#include <SFML/Graphics.hpp>
#include "game_state.hpp"

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

using namespace std;


class Play : public GameState
{
private:

	sf::Vector2f position;
	sf::Font font;
    int wormcount;
	/** Prepare the world */
	bool Player1Turn;
	sf::Text player1health;
	sf::Text player2health;
	Water water1;
	vector<Block> blocks;

	//sf::Texture grasstexture;
	sf::Texture backGroundTexture;
	sf::Texture CharacterTexture;
	//sf::Texture DirtTexture;
	sf::Texture CrosshairTexture;
	sf::Texture RocketTexture;

	sf::Texture dirttex;
	
	sf::Texture topStraighttex;
	sf::Texture leftStraighttex;
	sf::Texture topLeftCornertex;
	sf::Texture topRightCornertex;
	sf::Texture rightStraight;
	sf::Texture bottomStraight;
	sf::Texture bottomLeftCorner;

	sf::View player1View, player2View, bulletView;

	int sizeofmap;
	

	
	Player player1;
	Player player2;

	Crosshair cross;
	bool player1Fire;
	bool player2Fire;
	std::vector<Rocket> Rockets;
	sf::Sprite background;
	

	sf::CircleShape  boundingbox;
	 int width=200;
	 int heigh30;


public:

	virtual void draw();
	virtual void update();
	virtual void handleInput();
	void UpdateStaticBodies();
	void SwitchTurn();
	void UpdateCamera();
	void UpdateRockets();
	void UpdateHealth();
	void UpdateBlocks();
	void UpdateWater();
	Play(Game* game);
};

#endif /* GAME_STATE_EDITOR_HPP */