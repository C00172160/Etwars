#ifndef GAMEOVER_H
#define GAMEOVER_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "game_state.hpp"
#include "Menu.hpp"




class GameOver : public GameState
{
private:
	sf::Music BGM;
	sf::Text winner;
	sf::Font font;
	int Map;
	
	bool  vsync, audio, fullscreen;
	sf::Texture menu1, menu2,backgroundtex ;
	sf::Sprite menu1Sprite, menu2Sprite,backgroundsprite;
	sf::Vector2i Mouseposition;
	bool menu;

public:
	bool GameOver::CheckClicked(sf::Sprite sprite, sf::Vector2i position);
	virtual void draw();
	virtual void update();
	virtual void handleInput();
	
	GameOver(Game* game, std::string string,  int map, bool VSYNC, bool FULLSCREEN, bool AUDIO);
};

#endif /* GAME_STATE_START_HPP */