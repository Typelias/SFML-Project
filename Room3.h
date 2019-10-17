#pragma once
#include "Game.h"
#include "SplashState.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Wall.h"
#include "Door.h"

/*!
	Room3 creates the third room in the game
*/
class Room3 : public State
{
public:
	//! Constructor for the class. Takes game data as input.
	Room3(GameDataRef data);

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
	Enemy e1;

	//Objects
	Bullet b1;
	Bullet b2;

	//Walls and roads
	Wall bottomWall;
	Wall rightWall;
	Door leftDoor;
	Door topDoor;


	//Vectors
	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;
	std::vector<Wall*> Walls;
	std::vector<Door*> doors;

	//Functions
	bool canMove(Player p, sf::FloatRect rect);

	//Varibles
	size_t timer;
	bool isShooting;
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point stop;
	std::chrono::duration<double> elapsedTime;
	

};

