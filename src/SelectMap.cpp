

#include "SelectMap.hpp"


SelectMap::SelectMap(Game* game,int Map, bool VSYNC, bool FULLSCREEN, bool AUDIO)
{
	this->game = game;
	map = Map;
	vsync = VSYNC;
	fullscreen = FULLSCREEN;
	audio = AUDIO;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	game->window.setView(DefaultView);
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");


	 AtlantisText.setFont(font);
	 AtlantisText.setStyle(sf::Text::Bold);
	 AtlantisText.setCharacterSize(50);
	 AtlantisText.setColor(sf::Color::Black);
	 AtlantisText.setString("ATLANTIS");
	 AtlantisText.setPosition(sf::Vector2f(100, 50));


	 ElysiumText.setFont(font);
	 ElysiumText.setStyle(sf::Text::Bold);
	 ElysiumText.setCharacterSize(50);
	 ElysiumText.setColor(sf::Color::Black);
	 ElysiumText.setString("ELYSIUM");
	 ElysiumText.setPosition(sf::Vector2f(100, 200));


	 OlympusText.setFont(font);
	 OlympusText.setStyle(sf::Text::Bold);
	 OlympusText.setCharacterSize(50);
	 OlympusText.setColor(sf::Color::Black);
	 OlympusText.setString("OLYMPUS");
	 OlympusText.setPosition(sf::Vector2f(100, 350));

	 AtlantisTex.loadFromFile("Resources/background.jpg");
	 ElysiumTex.loadFromFile("Resources/forest.jpg");
	 OlympusTex.loadFromFile("Resources/volcano.jpg");
	 returnButtonTexture1.loadFromFile("Resources/menu1.png");
	 returnButtonTexture2.loadFromFile("Resources/menu2.png");
	 AtlantisSprite.setTexture(AtlantisTex);
	 AtlantisSprite.setScale(0.1, 0.1);
	 AtlantisSprite.setPosition(sf::Vector2f(400, -10) + AtlantisText.getPosition());
	
	 ElysiumSprite.setTexture(ElysiumTex);
	 ElysiumSprite.setScale(0.1, 0.1);
	 ElysiumSprite.setPosition(sf::Vector2f(400, -10) + ElysiumText.getPosition());

	 OlympusSprtite.setTexture(OlympusTex);
	 OlympusSprtite.setScale(0.1, 0.1);
	 OlympusSprtite.setPosition(sf::Vector2f(400, -10) + 
	 OlympusText.getPosition());

	 returnButton.setTexture(returnButtonTexture2);
	 returnButton.setPosition(sf::Vector2f(50, 500));
	
}
void SelectMap::draw()
{
	

	return;
}

void SelectMap::update()
{

	game->window.clear(sf::Color::Cyan);
	Mouseposition = sf::Mouse::getPosition(game->window);


	if (CheckClicked(AtlantisSprite, Mouseposition) == true)
	{
		AtlantisText.setColor(sf::Color::White);
		AtlantisSprite.setScale(0.12, 0.12);
	}
	else
	{
		AtlantisText.setColor(sf::Color::Black);
		AtlantisSprite.setScale(0.1, 0.1);
	}

	if (CheckClicked(ElysiumSprite, Mouseposition) == true)
	{
		ElysiumText.setColor(sf::Color::White);
		ElysiumSprite.setScale(0.12, 0.12);
	}
	else
	{
		ElysiumText.setColor(sf::Color::Black);
		ElysiumSprite.setScale(0.1, 0.1);
	}

	if (CheckClicked(OlympusSprtite, Mouseposition) == true)
	{
		OlympusText.setColor(sf::Color::White);
		OlympusSprtite.setScale(0.12, 0.12);
	}
	else
	{
		OlympusText.setColor(sf::Color::Black);
		OlympusSprtite.setScale(0.1, 0.1);
	}
	if (CheckClicked(returnButton, Mouseposition) == true)
	{
		returnButton.setTexture(returnButtonTexture1);
	}
	else
	{
		returnButton.setTexture(returnButtonTexture2);
	}

	game->window.draw(AtlantisText);
	game->window.draw(ElysiumText);
	game->window.draw(OlympusText);


	game->window.draw(AtlantisSprite);
	game->window.draw(ElysiumSprite);
	game->window.draw(OlympusSprtite);
	game->window.draw(returnButton);
	game->window.display();


	if (CheckClicked(AtlantisSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{

		map = 1;
		game->changeState(new Menu(this->game, map,vsync,fullscreen,audio));
	}
	if (CheckClicked(ElysiumSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		map = 2;
		game->changeState(new Menu(this->game, map, vsync, fullscreen, audio));
	}


	if (CheckClicked(OlympusSprtite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		map = 3;
		game->changeState(new Menu(this->game, map, vsync, fullscreen, audio));
	}

	if (CheckClicked(returnButton, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		map = 0;
		game->changeState(new Menu(this->game, map, vsync, fullscreen, audio));
	}

	

	

	


	

	return;


}

bool SelectMap::CheckClicked(sf::Sprite sprite, sf::Vector2i position)
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
SelectMap::~SelectMap()
{

	//while (!this->states.empty()) popState();
}

void SelectMap::handleInput()
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