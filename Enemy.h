#pragma once
#include <SFML/Graphics.hpp>
/*!
	Enemy is used to create the enemies in the game
*/
class Enemy : public sf::Drawable
{
public:
	/*!
		Constructor for the Enemy class.
		It takes in a hight, width and color.
	*/
	Enemy(float h = 100, float w = 50, sf::Color color = sf::Color::White);
	//!SetPos is used to set the position of the object. Is virtual so it can be overriden by children
	virtual void setPos(sf::Vector2f pos);
	//! getPos return a Vector2f with the bullets position
	sf::Vector2f getPos();
	//!draw is used to draw the object. Is virtual so it can be overriden by children.
	virtual void draw(sf::RenderTarget & w, sf::RenderStates SplashStates) const;
	//!globalBunds returns a FloatRect with the global bounds of the object. Is virtual so it can be overriden by children.
	virtual sf::FloatRect globalBounds();
	//!getSize returns a Vector2f with the size of the object. Is virtual so it can be overriden by children.
	virtual sf::Vector2f getSize();
	//!center returns a Vector2f with the kordinates for the center of the object. Is virtual so it can be overriden by children.
	virtual sf::Vector2f center();
	//!setTexture is used to set a texture to the object. Is virtual so it can be overriden by children.
	virtual void setTexture(sf::Texture &tex);


private:
	sf::RectangleShape body;
};

