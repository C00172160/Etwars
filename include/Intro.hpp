#ifndef INTRO_HPP
#define INTRO_HPP


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
#include <SFML\Audio.hpp>

#include "game_state.hpp"

class Intro : public GameState
{
private:

	sf::View view;
	sf::Clock clock;
	sf::Music Music1;
	sf::Texture introTex, textTex;
	sf::Sprite introSprite, textSprite;
	sf::Vector2f textPosition;
	bool change = false;
	float scaler = 1;
	
public:

	virtual void draw();
	virtual void update();
	virtual void handleInput();
	bool CheckClicked(sf::Sprite sprite, sf::Vector2i position);
	~Intro();
	Intro(Game* game);
};

#endif /* GAME_STATE_START_HPP */