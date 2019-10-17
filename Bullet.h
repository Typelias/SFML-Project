#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
/*!
	Bullet is used to create the projectiles in the game
*/
class Bullet : public sf::Drawable
{
public:
	/*!
		Constructor for the Bullet class.
		It takes a radius for the bullet and a boolean for it to know if
		it is a enemy bullet or a player bullet.
	*/
	Bullet(float radius = 5.f, bool isEnemy = false);
	//!globalBunds returns a FloatRect with the global bounds of the object
	sf::FloatRect globalBounds();
	//! SetPos is used to set the position of the object
	void setPos(sf::Vector2f pos);
	//! draw is used to draw the object
	void draw(sf::RenderTarget & w, sf::RenderStates SplashStates) const;
	//! moveForvard is used to move the bullet forvard with its calculated velocity
	void moveForvard();
	//!calculateVel is used to calculate the bllets velocity
	void calculateVel(sf::Vector2f start, sf::Vector2f target);
	//! getPos return a Vector2f with the bullets position
	sf::Vector2f getPos();
	//! isEnemy returns if the bullet is a enemy bullet or not
	bool isEnemy();
	
	int travel = 0; /*< travel is used to messure how far the bullet has traveled*/

private:
	sf::CircleShape shape;
	float speed;
	bool Enemy;
	sf::Vector2f currVelocity;



};



