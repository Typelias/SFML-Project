#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(GameDataRef data) : _data(data) {}

void ScoreBoard::Init()
{
	title.setFont(_data->assets.GetFont("text"));
	title.setFillColor(sf::Color::Red);
	title.setCharacterSize(100);
	title.setString("Scoreboard");
	title.setPosition(_data->window.getSize().x / 2.f - title.getGlobalBounds().width / 2.f, Wall_THICKNESS);

	pressEnter.setFont(_data->assets.GetFont("text"));
	pressEnter.setFillColor(sf::Color::Red);
	pressEnter.setCharacterSize(100);
	pressEnter.setString("Press enter to go to main manu");
	pressEnter.setPosition(_data->window.getSize().x / 2.f - pressEnter.getGlobalBounds().width / 2.f, _data->window.getSize().y - Wall_THICKNESS - pressEnter.getGlobalBounds().height);

	input.setFont(_data->assets.GetFont("text"));
	input.setFillColor(sf::Color::Red);
	input.setCharacterSize(50);

	in.open(LEADERBOARD);
	int i = 1;
	while (std::getline(in, tempName, ' '))
	{
		if (tempName == "")
			break;
		std::getline(in, tempTime);
		input.setString(std::to_string(i) + ": " + tempName + " " + tempTime);
		texts.push_back(input);
		i++;
	}
	for (int i = 0; i < texts.size(); i++)
	{
		texts[i].setPosition(_data->window.getSize().x / 2.f - texts[i].getGlobalBounds().width / 2.f, title.getPosition().y + (i+1)*2*Wall_THICKNESS);
	}


}

void ScoreBoard::HandleInput()
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

void ScoreBoard::Update(float dt)
{
	if (_data->input.keyIn(sf::Keyboard::Enter))
	{
		_data->machine.AddState(StateRef(new Menu(_data)));
	}
}

void ScoreBoard::Draw(float dt)
{
	_data->window.clear(sf::Color::Black);
	_data->window.draw(title);
	for ( int i = 0; i < texts.size(); i++)
	{
		_data->window.draw(texts[i]);
	}
	_data->window.draw(pressEnter);
	_data->window.display();
}
