#include "Enemy.h"


Enemy::Enemy(float h, float w, sf::Color color)
{
	body.setFillColor(color);
	body.setSize(sf::Vector2f(w, h));

}

void Enemy::setPos(sf::Vector2f pos)
{
	body.setPosition(pos);
}

sf::Vector2f Enemy::getPos()
{
	return body.getPosition();
}

void Enemy::draw(sf::RenderTarget & w, sf::RenderStates SplashStates) const
{
	w.draw(body);
}

sf::FloatRect Enemy::globalBounds()
{
	return body.getGlobalBounds();
}

sf::Vector2f Enemy::getSize()
{
	return body.getSize();
}

sf::Vector2f Enemy::center()
{
	return sf::Vector2f(body.getPosition().x + (body.getSize().x / 2), body.getPosition().y + (body.getSize().y / 2));
}

void Enemy::setTexture(sf::Texture & tex)
{
	body.setTexture(&tex);
}

