#ifndef  CONTROLS_HPP
#define  CONTROLS_HPP


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
#include "game_state.hpp"
#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "game_state.hpp"

class Controls : public GameState
{
private:

	sf::View view;
	sf::Text text;
	int Map;
	sf::Texture controls;
	bool  vsync, audio, fullscreen;
	sf::Texture menu1, menu2, backgrounds;
	sf::Sprite menu1Sprite, controlsButton, backgrounsSprite;
	sf::Vector2i windowPosition;
	sf::Vector2i Mouseposition;
	
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
	~Controls();
	Controls(Game* game, int map, bool VSYNC, bool FULLSCREEN, bool AUDIO);
};

#endif /* GAME_STATE_START_HPP */