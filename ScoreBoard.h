#pragma once
#include "State.h"
#include "Game.h"
#include "Menu.h"
#include <vector>
#include <fstream>
/*!
	ScoreBoard creates the scoreboard for the game menu
*/
class ScoreBoard : public State
{
public:
	//! Constructor for the class. Takes game data as input.
	ScoreBoard(GameDataRef data);
	//! Init runs at state creation to get everything ready
	void Init();
	//! Runs ever cykel to handle event input
	void HandleInput();
	//! Update runs every cykel after the event input is handled and runs the main parts of the state
	void Update(float dt);
	//! After we handled input and updates we need to display them and then we call update
	void Draw(float dt);
public:
	GameDataRef _data;
	sf::Text title;
	sf::Text input;
	sf::Text pressEnter;
	std::vector<sf::Text> texts;
	std::string tempName;
	std::string tempTime;
	std::fstream in;
	
};

