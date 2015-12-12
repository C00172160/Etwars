#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"

class Menu : public GameState
{
private:

	sf::View view;
	sf::Text text;
	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;
	sf::Vector2i windowPosition;
	sf::Vector2i Mouseposition;

public:

	virtual void draw();
	virtual void update();
	virtual void handleInput();
	bool CheckClicked(sf::Sprite sprite, sf::Vector2i position);

	Menu(Game* game);
};

#endif /* GAME_STATE_START_HPP */