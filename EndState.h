#pragma once
#include "SplashState.h"
#include "Game.h"
#include <utility>
#include <fstream>
#include <sstream>
#include "Menu.h"
#include "SplashState.h"
/*!
	EndStates creats the state when the player wins the game
*/
class EndState : public State
{
public:
	using Score = std::pair<std::string, double>;
	//! Constructor for the class. Takes game data as input.
	EndState(GameDataRef data);

	//! Init runs at state creation to get everything ready
	void Init();

	//! Runs ever cykel to handle event input
	void HandleInput();

	//! Update runs every cykel after the event input is handled and runs the main parts of the state
	void Update(float dt);

	//! After we handled input and updates we need to display them and then we call update
	void Draw(float dt);

private:
	GameDataRef _data;
	sf::Text displayPlayTime;
	sf::Text enterName;
	sf::Text PlayerIn;
	std::vector<Score> leaderboard;
	std::ifstream in;
	std::ofstream out;
	std::string tempName;
	std::string playTime;
	std::string PlayerInputString;
	double tempTime;
};

