#pragma once

#include <memory>
#include <string>
#include <time.h>
#include <chrono>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "DEFINITIONS.h"


/*!
	GameData is used to hold all the components for the game
*/
struct GameData
{
	StateMachine machine; /*!< An instanse of the state machine that runs the game*/
	sf::RenderWindow window;  /*!< An instanse of the window that shows the game*/
	AssetManager assets;  /*!< An instanse of the asset manager to handle the games assets*/
	InputManager input;  /*!< An instanse of the input manager to handle the event inputs*/
	//! getTime is used to get the elapsed time for the score
	double getTime()
	{
		return time.count();
	}
	//! addTime is used to add to the elapsed time
	void addTime(std::chrono::duration<double> newTime)
	{
		time += newTime;
	}
	//! zeroTime is used to reset the elapsed time
	void zeroTime()
	{
		time = std::chrono::duration<double>::zero();
	}


private:
	std::chrono::duration<double> time = std::chrono::duration<double>::zero();

};

/* \typedef GameDataRef
	GameDataRef is used to create the refrence pinter to the gamedata struct
*/
using GameDataRef = std::shared_ptr<GameData>;

/*!
	The Game class is the loop that runs the game. This is the only thing
	that is created in the main.cpp
*/

class Game
{
public:
	/*!
		Constructor for the Game class.
		It takes  a with and a hight for the game window. It also takes a
		title for the game window
	*/
	Game(int width, int height, std::string title);

private:
	const float dt = 1.f / 60.f;
	sf::Clock _clock;
	GameDataRef _data = std::make_shared<GameData>();
	

	void Run();
};




