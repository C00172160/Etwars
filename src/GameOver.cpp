
#include "GameOver.hpp"

#include "game_state.hpp"

GameOver::GameOver(Game* game, std::string string)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	menu1.loadFromFile("Resources/menu1.png");
	menu2.loadFromFile("Resources/menu2.png");
	menu1Sprite.setTexture(menu1);
	menu2Sprite.setTexture(menu2);
	menu1Sprite.setPosition(sf::Vector2f(300, 450));
	menu2Sprite.setPosition(sf::Vector2f(300, 450));
	game->window.setView(DefaultView);
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");
	winner.setString(string);
	winner.setFont(font);
	winner.setStyle(sf::Text::Bold);
	winner.setPosition(280, 300);
	winner.setCharacterSize(40);
	winner.setColor(sf::Color::Black);
	menu = false;
}
void GameOver::draw()
{
	return;
}

void GameOver::update()
{	
	Mouseposition = sf::Mouse::getPosition(game->window);
	game->window.clear(sf::Color::Cyan);
	game->window.draw(winner);
	
		
	
	game->window.draw(menu1Sprite);
	if (CheckClicked(menu1Sprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
	{
		game->window.draw(menu2Sprite);
	}
	if (CheckClicked(menu1Sprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		game->pushState(new Menu(this->game));
	}
	game->window.display();
	return;
}
bool GameOver::CheckClicked(sf::Sprite sprite, sf::Vector2i position)
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