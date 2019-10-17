#include "DeathState.h"


DeathState::DeathState(GameDataRef data):_data(data){}

void DeathState::Init()
{
	_data->assets.LoadTexture("death",DEATH_SCENE_BACKGROUND_FILEPATH);

	_background.setTexture(_data->assets.GetTexture("death"));
}

void DeathState::HandleInput()
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

void DeathState::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		_data->zeroTime();
		_data->machine.AddState(StateRef(new Menu(_data)));
	}

	if (_data->input.keyIn(sf::Keyboard::R))
	{
		_data->machine.AddState(StateRef(new Room1(_data)));
	}
}

void DeathState::Draw(float dt)
{
	_data->window.clear();
	_data->window.draw(_background);
	_data->window.display();
}
