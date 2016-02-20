#ifndef SETTINGS_HPP
#define SETTINGS_HPP


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

#include <SFML/Graphics.hpp>
#include "game_state.hpp"
#include "Menu.hpp"
#include "Play.hpp"
#include "game_state.hpp"

class Settings : public GameState
{
private:

	sf::View view;
	sf::Font font;

	int Map;
	sf::Vector2i windowPosition;
	sf::Vector2i Mouseposition;

	bool  vsync, audio, fullscreen;

	sf::Text FullscreenText;
	sf::Text VsyncText;
	sf::Text AudioText;
	sf::Text onText;
	sf::Text offText;

	sf::Texture tickOnTex, tickOffTex, returnButtonTexture1, returnButtonTexture2;
	sf::Sprite fullscreenONsprite, fullscreenOFFsprite, VsyncON, VsyncOFF, AudioON, AudioOFF, returnButton;

public:

	virtual void draw();
	virtual void update();
	virtual void handleInput();
	bool CheckClicked(sf::Sprite sprite, sf::Vector2i position);
	~Settings();
	Settings(Game* game,int map,bool VSYNC,bool FULLSCREEN,bool AUDIO);
};

#endif /* GAME_STATE_START_HPP */