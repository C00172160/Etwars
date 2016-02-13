

#include "Objectives.hpp"


Objectives::Objectives(Game* game, int map, bool VSYNC, bool FULLSCREEN, bool AUDIO)
{
	this->game = game;
	vsync = VSYNC;
	fullscreen = FULLSCREEN;
	audio = AUDIO;
	//states = game->states;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	game->window.setView(DefaultView);
	Map = map;
	objectives.loadFromFile("Resources/objectives.png");
	objectivesSprite.setTexture(objectives);
	
	controls.loadFromFile("Resources/menu1.png");
	controls2.loadFromFile("Resources/menu2.png");	
	controlsButton.setTexture(controls);
	controlsButton.setTextureRect(sf::IntRect(0, 0, controls.getSize().x, controls.getSize().y));
	controlsButton.setPosition(sf::Vector2f(50, 550 - (controlsButton.getGlobalBounds().height / 2)));
	
}
void Objectives::draw()
{
	return;
}

void Objectives::update()
{
	game->window.clear(sf::Color::Cyan);
	Mouseposition = sf::Mouse::getPosition(game->window);
	

	if (CheckClicked(controlsButton, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
	 {
		 controlsButton.setTexture(controls2);
	 }
	else if (CheckClicked(controlsButton, Mouseposition) == false)
	 {
		 controlsButton.setTexture(controls);
	 }
	else if (CheckClicked(controlsButton, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		game->pushState(new Menu(this->game, Map, vsync, fullscreen, audio));
	}
	
	
	

	game->window.draw(controlsButton);
	game->window.draw(objectivesSprite);

	game->window.display();
	
	return;
}

bool Objectives::CheckClicked(sf::Sprite sprite, sf::Vector2i position)
{

	if (position.x > sprite.getGlobalBounds().left
		&& position.x < (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width)
		&& position.y > sprite.getGlobalBounds().top
		&& position.y < (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height))
	{
		return true;
	}
	else
		return false;
}
Objectives::~Objectives()
{
}

void Objectives::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
			/* Resize the window */
		
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
			break;
		}
		default: break;
		}
	}

	return;
}