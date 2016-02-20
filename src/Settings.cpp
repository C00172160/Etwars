

#include "Settings.hpp"


Settings::Settings(Game* game,int map, bool VSYNC, bool FULLSCREEN, bool AUDIO)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	game->window.setView(DefaultView);
	Map = map;
	vsync = VSYNC;
	fullscreen = FULLSCREEN;
	audio = AUDIO;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");


	onText.setFont(font);
	onText.setStyle(sf::Text::Bold);
	onText.setCharacterSize(20);
	onText.setColor(sf::Color::Black);
	onText.setString("ON");
	onText.setPosition(sf::Vector2f(600, 25));


	offText.setFont(font);
	offText.setStyle(sf::Text::Bold);
	offText.setCharacterSize(20);
	offText.setColor(sf::Color::Black);
	offText.setString("OFF");
	offText.setPosition(sf::Vector2f(650, 25));

	VsyncText.setFont(font);
	VsyncText.setStyle(sf::Text::Bold);
	VsyncText.setCharacterSize(50);
	VsyncText.setColor(sf::Color::Black);
	VsyncText.setString("V-SYNC - ");
	VsyncText.setPosition(sf::Vector2f(100, 50));

	FullscreenText.setFont(font);
	FullscreenText.setStyle(sf::Text::Bold);
	FullscreenText.setCharacterSize(50);
	FullscreenText.setColor(sf::Color::Black);
	FullscreenText.setString("FULLSCREEN - ");
	FullscreenText.setPosition(sf::Vector2f(100, 200));

	AudioText.setFont(font);
	AudioText.setStyle(sf::Text::Bold);
	AudioText.setCharacterSize(50);
	AudioText.setColor(sf::Color::Black);
	AudioText.setString("BGM - ");
	AudioText.setPosition(sf::Vector2f(100, 350));

	
		tickOnTex.loadFromFile("Resources/tickFull.png");
		tickOffTex.loadFromFile("Resources/tickEmpty.png");
		returnButtonTexture1.loadFromFile("Resources/menu1.png");
		returnButtonTexture2.loadFromFile("Resources/menu2.png");

		if (fullscreen == true)
		{
			fullscreenONsprite.setTexture(tickOnTex);
			fullscreenOFFsprite.setTexture(tickOffTex);
		}
		else
		{
			fullscreenONsprite.setTexture(tickOffTex);
			fullscreenOFFsprite.setTexture(tickOnTex);
		}

		if (audio == true)
		{
			AudioON.setTexture(tickOnTex);
			AudioOFF.setTexture(tickOffTex);
		}
		else
		{
			AudioON.setTexture(tickOffTex);
			AudioOFF.setTexture(tickOnTex);
		}
		if (vsync == true)
		{
			VsyncON.setTexture(tickOnTex);
			VsyncOFF.setTexture(tickOffTex);
		}
		else
		{
			VsyncON.setTexture(tickOffTex);
			VsyncOFF.setTexture(tickOnTex);
		}




		VsyncON.setPosition(sf::Vector2f(600,75));
		VsyncOFF.setPosition(sf::Vector2f(650, 75));
	
		fullscreenONsprite.setPosition(sf::Vector2f(600, 225));
		fullscreenOFFsprite.setPosition(sf::Vector2f(650, 225));

		AudioON.setPosition(sf::Vector2f(600, 375));
		AudioOFF.setPosition(sf::Vector2f(650, 375));


		returnButton.setTexture(returnButtonTexture2);
		returnButton.setPosition(sf::Vector2f(50, 500));
}
void Settings::draw()
{
	





	


	return;
}

void Settings::update()
{
	game->window.clear(sf::Color::Yellow);



	Mouseposition = sf::Mouse::getPosition(game->window);



	if (CheckClicked(returnButton, Mouseposition) == true)
	{
		returnButton.setTexture(returnButtonTexture1);
	}
	else
	{
		returnButton.setTexture(returnButtonTexture2);
	}
	if (fullscreen == true)
	{
		fullscreenONsprite.setTexture(tickOnTex);
		fullscreenOFFsprite.setTexture(tickOffTex);
	}
	else
	{
		fullscreenONsprite.setTexture(tickOffTex);
		fullscreenOFFsprite.setTexture(tickOnTex);
	}

	if (audio == true)
	{
		AudioON.setTexture(tickOnTex);
		AudioOFF.setTexture(tickOffTex);
	}
	else
	{
		AudioON.setTexture(tickOffTex);
		AudioOFF.setTexture(tickOnTex);
	}
	if (vsync == true)
	{
		VsyncON.setTexture(tickOnTex);
		VsyncOFF.setTexture(tickOffTex);
	}
	else
	{
		VsyncON.setTexture(tickOffTex);
		VsyncOFF.setTexture(tickOnTex);
	}

	game->window.draw(VsyncText);
	game->window.draw(FullscreenText);
	game->window.draw(AudioText);
	game->window.draw(onText);
	game->window.draw(offText);
	game->window.draw(VsyncON);
	game->window.draw(VsyncOFF);
	game->window.draw(AudioON);
	game->window.draw(AudioOFF);
	game->window.draw(fullscreenONsprite);
	game->window.draw(fullscreenOFFsprite);
	game->window.draw(returnButton);
	game->window.display();


	if (CheckClicked(VsyncON, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		vsync = true;
		game->window.setVerticalSyncEnabled(true);
	}
	else if (CheckClicked(VsyncOFF, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		vsync = false;
		game->window.setVerticalSyncEnabled(false);
	}


	if (CheckClicked(fullscreenONsprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		fullscreen = true;
		game->window.create(sf::VideoMode(800, 600), "ET WARS",sf::Style::Fullscreen);
	}
	else if (CheckClicked(fullscreenOFFsprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		fullscreen = false;
		game->window.create(sf::VideoMode(800, 600), "ET WARS");
	}


	if (CheckClicked(AudioON, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		audio = true;
		
	}
	else if (CheckClicked(AudioOFF, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		audio = false;
	
	}
	if (CheckClicked(returnButton, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		
		game->changeState(new Menu(this->game, Map, vsync, fullscreen, audio));
	}



	return;


}

bool Settings::CheckClicked(sf::Sprite sprite, sf::Vector2i position)
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
Settings::~Settings()
{

	//while (!this->states.empty()) popState();
}

void Settings::handleInput()
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