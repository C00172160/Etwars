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
public:

	virtual void draw();
	virtual void update();
	virtual void handleInput();
	
	GameOver(Game* game, std::string string);
};

#endif /* GAME_STATE_START_HPP */