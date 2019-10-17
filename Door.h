#pragma once
#include "Game.h"
#include "DEFINITIONS.h"

/*!
	Door is used to create the door objects for the rooms
*/
class Door : public sf::Drawable
{
public:
	/*!
		Constructor for the Door class.
		It takes the game data and a bool to tell the dorr if it begins
		as a open door or not
	*/
	Door(GameDataRef data, bool open);
	//!Returns a FloatRect with the left/top(Depends on the door side) bounds
	sf::FloatRect sideABounds();
	//!Returns a FloatRect with the Right/bottom(Depends on the door side) bounds
	sf::FloatRect sideBBounds();
	//!Returns a Vector2f with the left/top(Depends on the door side) position
	sf::Vector2f sideAPos();
	//!Returns a Vector2f with the Right/bottom(Depends on the door side) position
	sf::Vector2f sideBPos();
	//! Opens the door 10 positions every run
	void open();
	//! Closes the door 10 position every run
	void close();
	//! draw is used to draw the object
	void draw(sf::RenderTarget & w, sf::RenderStates States) const;

	//!Used to make it a top door
	void makeTop();
	//!Used to make it a bot door
	void makeBot();
	//!Used to make it a right door
	void makeRight();
	//!Used to make it a left door
	void makeLeft();

private:
	GameDataRef _data;
	sf::RectangleShape sideA;
	sf::RectangleShape sideB;
	char type;
	bool isOpen;
	
};

