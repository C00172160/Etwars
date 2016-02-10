#ifndef GAMEOVER_H
#define GAMEOVER_H


#include <SFML/Graphics.hpp>
#include "game_state.hpp"
#include "Menu.hpp"




class GameOver : public GameState
{
private:

	sf::Text winner;
	sf::Font font;
	sf::Texture menu1, menu2;
	sf::Sprite menu1Sprite, menu2Sprite;
	sf::Vector2i Mouseposition;
	bool menu;
public:
	bool GameOver::CheckClicked(sf::Sprite sprite, sf::Vector2i position);
	virtual void draw();
	virtual void update();
	virtual void handleInput();
	
	GameOver(Game* game, std::string string);
};

#endif /* GAME_STATE_START_HPP */