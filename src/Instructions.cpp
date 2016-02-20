

#include "Instructions.hpp"


Instructions::Instructions(Game* game, int map, bool VSYNC, bool FULLSCREEN, bool AUDIO)
{
	this->game = game;
	//states = game->states;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	game->window.setView(DefaultView);
	Map = map;
	vsync = VSYNC;
	fullscreen = FULLSCREEN;
	audio = AUDIO;
	controls.loadFromFile("Resources/controls1.png");
	controls2.loadFromFile("Resources/controls2.png");
	objectives.loadFromFile("Resources/objectives1.png");
	objectives2.loadFromFile("Resources/objectives2.png");
	backgrounds.loadFromFile("Resources/menubackgrounds.png");
	backgrounsSprite.setTexture(backgrounds);
	controlsButton.setTexture(controls);
	objectivesButton.setTexture(objectives);
	controlsButton.setTextureRect(sf::IntRect(0, 0, controls.getSize().x, controls.getSize().y));
	controlsButton.setPosition(sf::Vector2f(400 - (controlsButton.getGlobalBounds().width / 2), 400 - (controlsButton.getGlobalBounds().height / 2)));
	objectivesButton.setPosition(sf::Vector2f(400 - (objectivesButton.getGlobalBounds().width / 2), 200 - (objectivesButton.getGlobalBounds().height / 2)));
}
void Instructions::draw()
{
	return;
}

void Instructions::update()
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
	
	
	if (CheckClicked(objectivesButton, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
	{
		objectivesButton.setTexture(objectives2);
	}
	else if (CheckClicked(objectivesButton, Mouseposition) == false)
	{
		objectivesButton.setTexture(objectives);
	}
	
	
	game->window.draw(backgrounsSprite);
	game->window.draw(controlsButton);
	game->window.draw(objectivesButton);
	
	game->window.display();

	 if (CheckClicked(objectivesButton, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	 {
		game->changeState(new Objectives(this->game,Map,vsync,fullscreen,audio));
	 }
	 else if (CheckClicked(controlsButton, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	 {
		 game->changeState(new Controls(this->game, Map, vsync, fullscreen, audio));
	 }
	
	return;
}

bool Instructions::CheckClicked(sf::Sprite sprite, sf::Vector2i position)
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
Instructions::~Instructions()
{
}

void Instructions::handleInput()
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