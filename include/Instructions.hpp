#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP


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
#include "Controls.hpp"
#include "Objectives.hpp"
#include "game_state.hpp"

#include "Play.hpp"
#include "game_state.hpp"

class Instructions : public GameState
{
private:

	sf::View view;
	sf::Text text;
	int Map;
	sf::Texture objectives,controls,controls2,objectives2, backgrounds;
	sf::Sprite objectivesButton,controlsButton, backgrounsSprite;
	sf::Vector2i windowPosition;
	sf::Vector2i Mouseposition;
	bool  vsync, audio, fullscreen;
	//std::stack<GameState*> states;
	sf::Vector2f p;
	sf::Texture texture;
	thor::ParticleSystem system;
	sf::Clock clock;
	thor::UniversalEmitter emitter;

public:

	virtual void draw();
	virtual void update();
	virtual void handleInput();
	bool CheckClicked(sf::Sprite sprite, sf::Vector2i position);
	~Instructions();
	Instructions(Game* game, int map, bool VSYNC, bool FULLSCREEN, bool AUDIO);
};

#endif /* GAME_STATE_START_HPP */