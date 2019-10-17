#include "SplashState.h"
#include <sstream>
#include <iostream>
#include "Room1.h"
#include "Room4.h"
#include "EndState.h"
#include "Menu.h"


SplashState::SplashState(GameDataRef data) : _data(data)
{

}

void SplashState::Init()
{
	_data->assets.LoadTexture("Splash SplashState Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
	_data->assets.LoadTexture("PlayerTexture", Player_TEXTURE);
	_data->assets.LoadTexture("Enemy", Enemy_TEXTURE);
	_data->assets.LoadTexture("boss", BOSS_TEXTURE);
	_data->assets.LoadFont("text", TEXT_FONT);
	_data->assets.LoadTexture("play", PLAY_TEXTURE);
	_data->assets.LoadTexture("score", SCORE_TEXTURE);

	_background.setTexture(_data->assets.GetTexture("Splash SplashState Background"));
	_data->zeroTime();
}

void SplashState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}
	}
}

void SplashState::Update(float dt)
{
	if (_clock.getElapsedTime().asSeconds() > SPLASH_SplashState_SHOW_TIME)
	{
		_data->machine.AddState(StateRef(new Menu(_data)));

		std::cout << "go to main menue" << std::endl;
	}
}

void SplashState::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);

	_data->window.display();
}


