#include "Menu.h"
#include <iostream>
#include "Room1.h"

Menu::Menu(GameDataRef data) : _data(data) {}

void Menu::Init()
{
	title.setFont(_data->assets.GetFont("text"));
	
	title.setString("Menu");
	title.setCharacterSize(100);
	title.setPosition(_data->window.getSize().x / 2.f - title.getGlobalBounds().width / 2.f, Wall_THICKNESS);
	title.setFillColor(sf::Color::Red);

	playButton.setTexture(_data->assets.GetTexture("play"));
	scoreButton.setTexture(_data->assets.GetTexture("score"));

	playButton.setPosition(_data->window.getSize().x / 2.f - playButton.getGlobalBounds().width / 2.f, _data->window.getSize().y / 2.f);
	scoreButton.setPosition(playButton.getPosition().x, playButton.getPosition().y + 2 * Wall_THICKNESS);
}

void Menu::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}
}

void Menu::Update(float dt)
{
	if (_data->input.IsSpriteClicked(playButton, sf::Mouse::Left, _data->window))
	{
		std::cout << "play Game \n";
		_data->machine.AddState(StateRef(new Room1(_data)));
	}
	else if (_data->input.IsSpriteClicked(scoreButton, sf::Mouse::Left, _data->window))
	{
		std::cout << "score board\n";
		_data->machine.AddState(StateRef(new ScoreBoard(_data)));
	}
}

void Menu::Draw(float dt)
{
	_data->window.clear(sf::Color::Black);
	_data->window.draw(title);
	_data->window.draw(playButton);
	_data->window.draw(scoreButton);
	_data->window.display();
}
