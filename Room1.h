#pragma once
#include "SplashState.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"
#include "Wall.h"
#include "Door.h"
#include <vector>
#include <cmath>

/*!
	Room1 creates the first room in the game
*/
class Room1 : public State
{
public:
	//! Constructor for the class. Takes game data as input.
	Room1(GameDataRef data);

	//! Init runs at state creation to get everything ready
	void Init();

	//! Runs ever cykel to handle event input
	void HandleInput();

	//! Update runs every cykel after the event input is handled and runs the main parts of the state
	void Update(float dt);

	//! After we handled input and updates we need to display them and then we call update
	void Draw(float dt);

private:
	//Game data
	GameDataRef _data; 

	//Characters
	Player p1; 

	//Objects
	Bullet b1; 

	//Walls and roads
	Wall bottomWall; 
	Wall rightWall; 
	Wall leftWall; 
	Door topDoor; 

	//Vectors
	std::vector<Bullet> bullets; 
	std::vector<Wall> Walls; 

	//Functions
	bool canMove(Player p, sf::FloatRect rect); 

	//Varibles
	bool isShooting = false; 
	std::chrono::high_resolution_clock::time_point start; 
	std::chrono::high_resolution_clock::time_point stop; 
	std::chrono::duration<double> elapsedTime;  
	
};

