#ifndef SELECTMAP_HPP
#define SELECTMAP_HPP


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

class SelectMap : public GameState
{
private:

	sf::View view;
	sf::Font font;

	int map = 0;
	sf::Vector2i windowPosition;
	sf::Vector2i Mouseposition;

	thor::ParticleSystem system;
	sf::Clock clock;
	thor::UniversalEmitter emitter;

	sf::Text AtlantisText;
	sf::Text ElysiumText;
	sf::Text OlympusText;
	bool  vsync, audio, fullscreen;
	sf::Texture AtlantisTex, ElysiumTex, OlympusTex, returnButtonTexture1, returnButtonTexture2;
	sf::Sprite AtlantisSprite, ElysiumSprite, OlympusSprtite,returnButton;

public:

	virtual void draw();
	virtual void update();
	virtual void handleInput();
	bool CheckClicked(sf::Sprite sprite, sf::Vector2i position);
	~SelectMap();
	SelectMap(Game* game,int Map, bool VSYNC, bool FULLSCREEN, bool AUDIO);
};

#endif /* GAME_STATE_START_HPP */