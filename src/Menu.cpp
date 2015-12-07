#include <SFML/Graphics.hpp>

#include "Menu.hpp"
#include "Play.hpp"
#include "game_state.hpp"

Menu::Menu(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);


	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	//create a formatted text string
	
	text.setFont(font);
	text.setString("Hello World");
	text.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	text.setPosition(20, 40);
	text.setCharacterSize(40);
	
}
void Menu::draw()
{
	this->game->window.setView(this->view);

	this->game->window.clear(sf::Color::White);
	this->game->window.draw(text);

	return;
}

void Menu::update()
{
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