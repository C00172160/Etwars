#include <SFML/Graphics.hpp>

#include "Menu.hpp"
#include "Intro.hpp"
#include "game_state.hpp"
#include <ctime>
#include <iostream>

using namespace std;

Intro::Intro(Game* game)
{

	this->game = game;
	        // By default, the internal buffer will hold 44100 samples
	Music1.openFromFile("Resources/music.wav");
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	game->window.setView(DefaultView);
	introTex.loadFromFile("Resources/intro.png");
	textTex.loadFromFile("Resources/starwars.png");
	//this->view.setSize(pos);
	
	introSprite.setTexture(introTex);
	introSprite.setOrigin(400, 300);
	textSprite.setTexture(textTex);
	textPosition = sf::Vector2f(0, 800);
	textSprite.setPosition(textPosition);
	Music1.play();
   
}

void Intro::draw()
{
	return;
}

void Intro::update()
{
	game->window.clear(sf::Color::Black);

	introSprite.setScale(scaler, scaler);
	introSprite.setPosition(sf::Vector2f(400,300));
	if (scaler > 0.025)
	{
		game->window.draw(introSprite);
		scaler -= 0.001;
	}
	else
	{
		textPosition.y-=1.5;
		textSprite.setPosition(textPosition);
		game->window.draw(textSprite);

		

	}

	
	
	game->window.display();
	
	if (textSprite.getPosition().y + textSprite.getGlobalBounds().height < 0)
	{
		change = true;
	
		
	}
	if (change == true)
	{
		Music1.stop();
		game->changeState(new Menu(this->game, 0,true,true,true));
	}


	
	return;


}


Intro::~Intro()
{

}

void Intro::handleInput()
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
		
			if (event.key.code == sf::Keyboard::Escape)
			{
				this->game->window.close();
				break;
			}
			if (event.key.code == sf::Keyboard::Space)
			{
				change = true;
				break;
			}
		}
		
		default: break;
		}
	}

	return;
}