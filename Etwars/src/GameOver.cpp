
#include "GameOver.hpp"

#include "game_state.hpp"

GameOver::GameOver(Game* game, std::string string)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	game->window.setView(DefaultView);
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	winner.setString(string);
	winner.setFont(font);
	winner.setStyle(sf::Text::Bold);
	winner.setPosition(400, 300);
	winner.setCharacterSize(40);
	winner.setColor(sf::Color::Black);

	

}
void GameOver::draw()
{



	return;
}

void GameOver::update()
{
	
	game->window.clear(sf::Color::Cyan);
	
	game->window.draw(winner);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		game->pushState(new Menu(this->game));
	}

	game->window.display();

	return;

}


void GameOver::handleInput()
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