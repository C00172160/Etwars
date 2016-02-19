#include <SFML/Graphics.hpp>

#include "Menu.hpp"
#include "Play.hpp"
#include "game_state.hpp"

Menu::Menu(Game* game)
{
	this->game = game;
	//states = game->states;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	game->window.setView(DefaultView);

	//this->view.setSize(pos);
	name.loadFromFile("Resources/ETWARS.png");
	nameSprite.setTexture(name);
	selectTexture.loadFromFile("Resources/selectmap.png");
	selectSprite.setTexture(selectTexture);
	selectSprite.setPosition(sf::Vector2f(300,400));
	nameSprite.setPosition(290, 150);
	buttonTexture.loadFromFile("Resources/startbutton.png");
	//buttonSprite.setTexture(buttonTexture);
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setTextureRect(sf::IntRect(0, 0, 201, 71));
	buttonSprite.setPosition(sf::Vector2f(400 - (buttonSprite.getGlobalBounds().width / 2), 300 - (buttonSprite.getGlobalBounds().height / 2)));
	rock.loadFromFile("Resources/rock.png");
	rockVel = sf::Vector2f(850, 850);
	gravity = 9.81;
	mass = 5;
	weight = mass * gravity;
	rockSprite.setTexture(rock);
	rockPos = sf::Vector2f(-50, 250);
	rockSprite.setPosition(rockPos);
	m_acceleration = sf::Vector2f(0, weight * gravity);
	physics = false;
	//windowPosition = sf::Vector2i(buildView.getCenter().x - 400, buildView.getCenter().y - 300);
}
void Menu::draw()
{
	return;
}
void Menu::reset()
{
	rockVel = sf::Vector2f(850, 850);
	gravity = -9.81;
	mass = 5;
	weight = mass * gravity;
	rockPos = sf::Vector2f(-50, 250);
	m_acceleration = sf::Vector2f(0, weight);

}

void Menu::update()
{
	game->window.clear(sf::Color::Cyan);
	//v = u + at 
	// s = ut + 1 / 2atsquared
	deltaTime = clock.restart().asSeconds();
	if (physics == true)
	{
		
		rockVel.y = rockVel.y + m_acceleration.y  * deltaTime;
		rockPos += rockVel*deltaTime + 0.5f *(m_acceleration *(deltaTime * deltaTime));
		rockSprite.setPosition(rockPos);
	} 
	
	/*if (rockVel.x > 2)
	{
		int i = 0;
	}*/

	Mouseposition = sf::Mouse::getPosition(game->window);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(500, 200), 5));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		physics = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		physics = false;
		reset();
	}

	 if (CheckClicked(buttonSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)==false)
	 {
		 buttonSprite.setTextureRect(sf::IntRect(0, 72, 201, 71));
	 }
	 else if (CheckClicked(buttonSprite, Mouseposition) == false)
	 {
		 buttonSprite.setTextureRect(sf::IntRect(0, 0, 201, 71));
	 }
	

	game->window.draw(buttonSprite);
	game->window.draw(nameSprite);
	game->window.draw(selectSprite);
	game->window.draw(rockSprite);
	game->window.display();
	
	
	 if (CheckClicked(buttonSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	 {
		 buttonSprite.setTextureRect(sf::IntRect(0, 144, 201, 71));
		 game->changeState(new Play(this->game));
	 }

	return;
		
	
}

bool Menu::CheckClicked(sf::Sprite sprite, sf::Vector2i position)
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
Menu::~Menu()
{

	//while (!this->states.empty()) popState();
}

void Menu::handleInput()
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