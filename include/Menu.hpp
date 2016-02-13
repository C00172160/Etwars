#ifndef MENU_HPP
#define MENU_HPP


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
#include "Play.hpp"
#include "SelectMap.hpp"
#include "game_state.hpp"
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Instructions.hpp"
#include "Settings.hpp"
#include "game_state.hpp"

class Menu : public GameState
{
private:

	sf::View view;
	sf::Text text;

	sf::Texture buttonTexture, name, selectTexture1,selectTexture2, backgroundTex, instructionsbuttonTexture1, instructionsbuttonTexture2,Settings1tex,settings2Tex,exitTex1,exitTex2;
	sf::Sprite buttonSprite, nameSprite,selectSprite,backgroundSprite,instructionbuttonSprite,SettingsButtonSprite,exitbuttonSprite;
	sf::Vector2i windowPosition;
	sf::Vector2i Mouseposition;


	sf::Texture texture;
	thor::ParticleSystem system;
	sf::Clock clock;
	thor::UniversalEmitter emitter;
	bool  vsync, audio, fullscreen;
	int currentMap;
	int returnedMap = 0;
public:

	virtual void draw();
	virtual void update();
	virtual void handleInput();
	bool CheckClicked(sf::Sprite sprite, sf::Vector2i position);
	~Menu();

	Menu(Game* game, int returnedMAP,bool VSYNC, bool FULLSCREEN, bool AUDIO);
};

#endif /* GAME_STATE_START_HPP */