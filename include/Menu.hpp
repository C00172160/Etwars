#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class Menu : public GameState
{
private:

	sf::View view;
	sf::Text text;

public:

	virtual void draw();
	virtual void update();
	virtual void handleInput();

	Menu(Game* game);
};

#endif /* GAME_STATE_START_HPP */