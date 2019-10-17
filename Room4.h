#pragma once
#include "SplashState.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Wall.h"
#include "Door.h"
#include "Boss.h"

/*!
	Room4 creates the forth room in the game
*/
class Room4 : public State
{
public:
	//! Constructor for the class. Takes game data as input.
	Room4(GameDataRef data);
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
	Boss boss;

	//Objects
	Bullet b1;
	Bullet b2;

	//Walls and roads
	Wall leftWall;
	Wall rightWall;
	Door topDoor;
	Door bottomDoor;
	
	//Vectors
	//std::vector<Wall*> Walls;
	std::vector<Bullet> bullets;
	//std::vector<Door*> doors;
	std::vector<int> toErase;
	std::vector<sf::Drawable*> draws;

	//Functions
	bool canMove(Player p, sf::FloatRect rect);

	//Varibles
	sf::Vector2f left;
	sf::Vector2f right;
	size_t timer;
	bool isShooting;
	bool erasing;
	bool setTime = true;
	int hits;
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point stop;
	std::chrono::duration<double> elapsedTime;
};

