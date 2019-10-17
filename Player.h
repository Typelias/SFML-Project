#pragma once
#include <SFML/Graphics.hpp>
/*!
	Constructor for the Player class.
*/
class Player : public sf::Drawable
{
public:
	Player();
	//! draw is used to draw the object
	void draw(sf::RenderTarget & w, sf::RenderStates SplashStates) const;
	//!globalBunds returns a FloatRect with the global bounds of the object
	sf::FloatRect globalBounds();
	//!center returns a Vector2f with the kordinates for the center of the object
	sf::Vector2f center();
	//!setTexture is used to set a texture to the object
	void setTexture(sf::Texture& tex);
	//!move is used to move the object forvard
	void move(float x, float y);
	//! SetPos is used to set the position of the object
	void setPos(float x, float y);
	//!getSize returns a Vector2f with the size of the object
	sf::Vector2f getSize();
	//! getPos return a Vector2f with the bullets position
	sf::Vector2f getPos();

private:
	sf::RectangleShape body;
};



