#include "Game.h"
#include "SplashState.h"



Game::Game(int width, int height, std::string title)
{

	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	_data->window.setFramerateLimit(60);

	_data->machine.AddState(StateRef(new SplashState(this->_data)));

	Run();
}

void Game::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = _clock.getElapsedTime().asSeconds();

	float accumulator = 0.f;

	while (this->_data->window.isOpen())
	{
		this->_data->machine.ProcessStateChanges();

		newTime = _clock.getElapsedTime().asSeconds();

		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->machine.GetActiveState()->HandleInput();
			this->_data->machine.GetActiveState()->Update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->_data->machine.GetActiveState()->Draw(interpolation);
	}

}