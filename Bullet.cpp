#include "Bullet.h"



Bullet::Bullet(float radius, bool isEnemy) :currVelocity(0.f, 0.f), speed(15.f), Enemy(isEnemy)
{
	shape.setRadius(radius);
	if (Enemy)
		shape.setFillColor(sf::Color::Red);
	else
		shape.setFillColor(sf::Color::Blue);
}

sf::FloatRect Bullet::globalBounds()
{
	return shape.getGlobalBounds();
}

void Bullet::setPos(sf::Vector2f pos)
{
	shape.setPosition(pos);
}

void Bullet::draw(sf::RenderTarget & w, sf::RenderStates States) const
{
	w.draw(shape);
}


void Bullet::moveForvard()
{
	shape.move(currVelocity);
}

void Bullet::calculateVel(sf::Vector2f start, sf::Vector2f target)
{
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	aimDir = target - start;
	aimDirNorm = aimDir / float(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

	currVelocity = aimDirNorm * speed;
}

sf::Vector2f Bullet::getPos()
{
	return shape.getPosition();
}

bool Bullet::isEnemy()
{
	return Enemy;
}


