#include "EndState.h"
#include <iostream>

using Score = EndState::Score;

EndState::EndState(GameDataRef data) : _data(data)
{
	std::ostringstream strs;
	strs << _data->getTime();
	playTime = "Din tid var: " +  strs.str();

	enterName.setFont(_data->assets.GetFont("text"));
	enterName.setString("Please enter your name:");
	displayPlayTime.setFont(_data->assets.GetFont("text"));
	displayPlayTime.setString(playTime);
	PlayerIn.setFont(_data->assets.GetFont("text"));

	displayPlayTime.setCharacterSize(100);
	enterName.setCharacterSize(100);
	PlayerIn.setCharacterSize(100);

	displayPlayTime.setPosition(_data->window.getSize().x / 2.f - displayPlayTime.getGlobalBounds().width / 2.f, Wall_THICKNESS);
	displayPlayTime.setFillColor(sf::Color::Red);
	enterName.setPosition(_data->window.getSize().x / 2.f - enterName.getGlobalBounds().width / 2.f, displayPlayTime.getPosition().y + 4*Wall_THICKNESS);
	enterName.setFillColor(sf::Color::Red);
	PlayerIn.setFillColor(sf::Color::Red);

	in.open(LEADERBOARD);
	std::string temp;
	while(std::getline(in, tempName, ' '))
	{
		if (tempName == "")
			break;
		std::getline(in, temp);

		tempTime = std::stod(temp);
		
		std::cout << tempName << " " << tempTime << std::endl;
		leaderboard.push_back(std::make_pair(tempName, tempTime));
	}

	out.open(LEADERBOARD);
}

void EndState::Init()
{
}

void EndState::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			std::sort(leaderboard.begin(), leaderboard.end(), [](Score e, Score f)
			{
				return e.second < f.second;
			});
			std::for_each(leaderboard.begin(), leaderboard.end(), [&](Score a)
			{
				std::cout << a.first << " " << a.second << std::endl;
				out << a.first << " " << a.second << std::endl;
			});
			
			this->_data->window.close();
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode >= 33)
			{
				PlayerInputString += (event.text.unicode);
				PlayerIn.setString(PlayerInputString);
				std::cout << PlayerInputString << "\n";
			}
			else if (event.text.unicode == 8 && !PlayerInputString.empty())
			{
				
				PlayerInputString = PlayerInputString.substr(0, PlayerInputString.size() - 1);
				PlayerIn.setString(PlayerInputString);
				std::cout << PlayerInputString << "\n";

			}
			
		}
		
		
	}
}

void EndState::Update(float dt)
{


	PlayerIn.setPosition(_data->window.getSize().x / 2.f - PlayerIn.getGlobalBounds().width / 2.f, enterName.getPosition().y + 2*Wall_THICKNESS);


	if (_data->input.keyIn(sf::Keyboard::Enter))
	{
		leaderboard.push_back(std::make_pair(PlayerInputString, _data->getTime()));
		std::sort(leaderboard.begin(), leaderboard.end(), [&](Score e, Score f)
		{
			return e.second < f.second;
		});
		while (leaderboard.size() > 5)
		{
			leaderboard.pop_back();
		}
		std::for_each(leaderboard.begin(), leaderboard.end(), [&](Score a)
		{
			std::cout << a.first << " " << a.second << std::endl;
			out << a.first << " " << a.second << std::endl;
		});
		std::cout << leaderboard.size() << "\n";
		
		std::cout << "\n";
		_data->machine.AddState(StateRef(new Menu(_data)));
	}
	
}

void EndState::Draw(float dt)
{
	_data->window.clear(sf::Color::Black);

	_data->window.draw(displayPlayTime);
	_data->window.draw(enterName);
	_data->window.draw(PlayerIn);

	_data->window.display();
}
