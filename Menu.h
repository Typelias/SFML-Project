#pragma once
#include "SplashState.h"
#include "Game.h"
#include "Room1.h"
#include "ScoreBoard.h"

/*!
	Menu creates the main menue in the game
*/
class Menu : public State
{
public:
	//! Constructor for the class. Takes game data as input.
	Menu(GameDataRef data);
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
	sf::Sprite playButton;
	sf::Sprite scoreButton;
	sf::Text title;
};

