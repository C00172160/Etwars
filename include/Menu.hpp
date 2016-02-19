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

#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class Menu : public GameState
{
private:

	sf::View view;
	sf::Text text;

	sf::Texture buttonTexture, name,selectTexture;
	sf::Sprite buttonSprite, nameSprite,selectSprite;
	sf::Vector2i windowPosition;
	sf::Vector2i Mouseposition;
	sf::Texture rock;
	sf::Sprite rockSprite;
	bool physics;
	float mass, deltaTime, weight, gravity;
	sf::Vector2f rockPos, rockVel, m_acceleration;
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
	void reset();
	~Menu();
	Menu(Game* game);
};

#endif /* GAME_STATE_START_HPP */