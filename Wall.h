#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"
/*!
	Wall is used to create the wall objects for the rooms
*/
class Wall : public sf::Drawable
{
public:
	/*!
		Constructor for the Wall class.
		It takes the game data as input
	*/
	Wall(GameDataRef data);
	//!Returns a Vector2f with the position of the object
	sf::Vector2f getPos();
	//!globalBunds returns a FloatRect with the global bounds of the object
	sf::FloatRect globalBounds();
	//! draw is used to draw the object
	void draw(sf::RenderTarget &w, sf::RenderStates States) const;

	//! Used to set the wall as a right wall
	void setRight();
	//! Used to set the wall as a left wall
	void setLeft();
	//! Used to set the wall as a top wall
	void setTop();
	//! Used to set the wall as a bottom wall
	void setBot();

private:
	GameDataRef _data;
	sf::RectangleShape body;
};

