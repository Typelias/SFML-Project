#pragma once
#include "Enemy.h"
/*!
	Boss creates the final boss in the game
*/
class Boss : public Enemy
{
public:
	/*!
		Constructor for the BOss class.
		It takes in a hight, width and color.
	*/
	Boss(float h = 200, float w = 100, sf::Color color = sf::Color::White);
	//! SetPos is used to set the position of the object
	void setPos(sf::Vector2f pos);
	//! draw is used to draw the object
	void draw(sf::RenderTarget & w, sf::RenderStates States) const;
	//!getSize returns a Vector2f with the size of the object
	sf::Vector2f getSize();
	//!center returns a Vector2f with the kordinates for the center of the object
	sf::Vector2f center();
	//!globalBunds returns a FloatRect with the global bounds of the object
	sf::FloatRect globalBounds();
	//!setTexture is used to set a texture to the object
	void setTexture(sf::Texture &tex);
private:
	sf::RectangleShape body;
};

