

#include "Menu.hpp"



Menu::Menu(Game* game, int returnedMAP, bool VSYNC, bool FULLSCREEN, bool AUDIO)
{
	srand(time(NULL));
	if (returnedMAP == 0)
	{
		currentMap = (rand() % 3) + 1;
	}
	else
	{
		currentMap = returnedMAP;
	}


	vsync = VSYNC;
	fullscreen = FULLSCREEN;
	audio = AUDIO;
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	sf::View DefaultView;
	DefaultView.setCenter(400, 300);
	DefaultView.setSize(800, 600);
	game->window.setView(DefaultView);

	//this->view.setSize(pos);
	name.loadFromFile("Resources/ETWARS.png");
	nameSprite.setTexture(name);
	selectTexture1.loadFromFile("Resources/selectmap1.png");
	selectTexture2.loadFromFile("Resources/selectmap2.png");
	selectSprite.setTexture(selectTexture1);
	selectSprite.setPosition(game->window.getSize().x / 2 - selectSprite.getGlobalBounds().width / 2, 200);

	Settings1tex.loadFromFile("Resources/settings1.png");
	settings2Tex.loadFromFile("Resources/settings2.png");
	SettingsButtonSprite.setTexture(selectTexture1);
	SettingsButtonSprite.setPosition(game->window.getSize().x / 2 - SettingsButtonSprite.getGlobalBounds().width / 2, 400);

	nameSprite.setPosition(game->window.getSize().x/2-nameSprite.getGlobalBounds().width/2, 10);
	buttonTexture.loadFromFile("Resources/startbutton.png");
	//buttonSprite.setTexture(buttonTexture);
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setTextureRect(sf::IntRect(0, 0, 201, 71));
	buttonSprite.setPosition(game->window.getSize().x / 2 - buttonSprite.getGlobalBounds().width / 2, 100);
	//windowPosition = sf::Vector2i(buildView.getCenter().x - 400, buildView.getCenter().y - 300);
	backgroundTex.loadFromFile("Resources/menuBackground.png");

	backgroundSprite.setTexture(backgroundTex);
	backgroundSprite.setPosition(sf::Vector2f(0, 0));


	instructionsbuttonTexture1.loadFromFile("Resources/instructions1.png");
	instructionsbuttonTexture2.loadFromFile("Resources/instructions2.png");
	instructionbuttonSprite.setTexture(selectTexture1);
	instructionbuttonSprite.setPosition(game->window.getSize().x / 2 - selectSprite.getGlobalBounds().width / 2, 300);

	exitTex1.loadFromFile("Resources/exit1.png");
	exitTex2.loadFromFile("Resources/exit2.png");
	exitbuttonSprite.setTexture(exitTex1);
	exitbuttonSprite.setPosition(game->window.getSize().x / 2 - exitbuttonSprite.getGlobalBounds().width / 2, 500);
}

void Menu::draw()
{
	return;
}


void Menu::update()
{
	game->window.clear(sf::Color::Cyan);
	Mouseposition = sf::Mouse::getPosition(game->window);
	

	 if (CheckClicked(buttonSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)==false)
	 {
		 buttonSprite.setTextureRect(sf::IntRect(0, 72, 201, 71));
	 }
	 else if (CheckClicked(buttonSprite, Mouseposition) == false)
	 {
		 buttonSprite.setTextureRect(sf::IntRect(0, 0, 201, 71));
	 }
	

	 if (CheckClicked(instructionbuttonSprite, Mouseposition) == true)
	 {
		 instructionbuttonSprite.setTexture(instructionsbuttonTexture2);
	 }
	 else
	 {
		 instructionbuttonSprite.setTexture(instructionsbuttonTexture1);
	 }
	 if (CheckClicked(SettingsButtonSprite, Mouseposition) == true)
	 {
		 SettingsButtonSprite.setTexture(settings2Tex);
	 }
	 else
	 {
		 SettingsButtonSprite.setTexture(Settings1tex);
	 }
	 if (CheckClicked(selectSprite, Mouseposition) == true)
	 {
		 selectSprite.setTexture(selectTexture2);
	 }
	 else
	 {
		 selectSprite.setTexture(selectTexture1);
	 }
	 if (CheckClicked(exitbuttonSprite, Mouseposition) == true)
	 {
		 exitbuttonSprite.setTexture(exitTex2);
	 }
	 else
	 {
		 exitbuttonSprite.setTexture(exitTex1);
	 }
	
	game->window.draw(backgroundSprite);
	game->window.draw(buttonSprite);
	game->window.draw(nameSprite);
	game->window.draw(selectSprite);
	game->window.draw(SettingsButtonSprite);
	game->window.draw(exitbuttonSprite);
	game->window.draw(instructionbuttonSprite);
	game->window.display();
	 
	
	 if (CheckClicked(buttonSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	 {
		 buttonSprite.setTextureRect(sf::IntRect(0, 144, 201, 71));
		 game->changeState(new Play(this->game, currentMap,vsync,fullscreen,audio));
	 }
	
	 if (CheckClicked(selectSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	 {	
		 game->changeState(new SelectMap(this->game, currentMap, vsync, fullscreen, audio));
	 }
	 if (CheckClicked(exitbuttonSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	 {
		 this->game->window.close();
	 }
	 if (CheckClicked(instructionbuttonSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	 {
		// game->changeState(new Instructions(this->game, currentMap, vsync, fullscreen, audio));
		 game->changeState(new GameOver(this->game, "", currentMap, vsync, fullscreen, audio));
	 }
	 if (CheckClicked(SettingsButtonSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	 {

		 game->changeState(new Settings(this->game, currentMap, vsync, fullscreen, audio));
	 }

	return;
		
	
}

bool Menu::CheckClicked(sf::Sprite sprite, sf::Vector2i position)
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

Menu::~Menu()
{

}

void Menu::handleInput()
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