#include <SFML/Graphics.hpp>

#include "Menu.hpp"
#include "Play.hpp"
#include "game_state.hpp"

Menu::Menu(Game* game)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	buttonTexture.loadFromFile("Resources/startbutton.png");
	//buttonSprite.setTexture(buttonTexture);
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setTextureRect(sf::IntRect(0, 0, 201, 71));
	buttonSprite.setPosition(sf::Vector2f(400 - (buttonSprite.getGlobalBounds().width / 2), 300 - (buttonSprite.getGlobalBounds().height / 2)));
	//windowPosition = sf::Vector2i(buildView.getCenter().x - 400, buildView.getCenter().y - 300);


	texture.loadFromFile("Resources/fire.png");
	system.setTexture(texture);
	emitter.setEmissionRate(1000);
	emitter.setParticleLifetime(thor::Distributions::uniform(sf::seconds(0.1), sf::seconds(0.2)));
	emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(300,200), 5));   // Emit particles in given circle
	emitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(300,500), 5.f)); // Emit towards direction with deviation of 15°
	emitter.setParticleRotation(thor::Distributions::uniform(0.f, 360.f));      // Rotate randomly
	system.addEmitter(thor::refEmitter(emitter));


	sf::Vector2f p(10, 10);
}
void Menu::draw()
{
	
	

	return;
}

void Menu::update()
{
	system.update(clock.restart());




	game->window.clear(sf::Color::Cyan);
	Mouseposition = sf::Mouse::getPosition(game->window);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(500, 200), 5));
	}

	if (CheckClicked(buttonSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)==false)
	 {
		 buttonSprite.setTextureRect(sf::IntRect(0, 72, 201, 71));
	 }
	 else if (CheckClicked(buttonSprite, Mouseposition) == false)
	 {
		 buttonSprite.setTextureRect(sf::IntRect(0, 0, 201, 71));
	 }
	else if (CheckClicked(buttonSprite, Mouseposition) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == true)
	{
		buttonSprite.setTextureRect(sf::IntRect(0, 144, 201, 71));
		game->pushState(new Play(this->game));
	}

	game->window.draw(buttonSprite);
	game->window.draw(system);
		game->window.display();

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