

#include "Controls.hpp"


Controls::Controls(Game* game, int map, bool VSYNC, bool FULLSCREEN, bool AUDIO)
{
	this->game = game;
	vsync = VSYNC;
	fullscreen = FULLSCREEN;
	audio = AUDIO;
	//states = game->states;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	game->window.setView(DefaultView);
	backgrounds.loadFromFile("Resources/red.png");
	backgrounsSprite.setTexture(backgrounds);
	menu1.loadFromFile("Resources/menu1.png");
	menu2.loadFromFile("Resources/menu2.png");
	menu1Sprite.setTexture(menu1);
	menu1Sprite.setPosition(sf::Vector2f(20, 520));
	controls.loadFromFile("Resources/Instructions.png");
	controlsButton.setTexture(controls);
	Map = map;
}
void Controls::draw()
{
	return;
}

void Controls::update()
{
	game->window.clear(sf::Color::Cyan);
	Mouseposition = sf::Mouse::getPosition(game->window);
	

	if (CheckClicked(menu1Sprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
	 {
		 menu1Sprite.setTexture(menu2);
	 }
	else if (CheckClicked(menu1Sprite, Mouseposition) == false)
	 {
		 menu1Sprite.setTexture(menu1);
	 }
	
	
	
	game->window.draw(backgrounsSprite);
	game->window.draw(menu1Sprite);
	game->window.draw(controlsButton);
	game->window.display();
    if (CheckClicked(menu1Sprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		game->changeState(new Menu(this->game, Map, vsync, fullscreen, audio));
	}

	return;
}

bool Controls::CheckClicked(sf::Sprite sprite, sf::Vector2i position)
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
Controls::~Controls()
{
}

void Controls::handleInput()
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