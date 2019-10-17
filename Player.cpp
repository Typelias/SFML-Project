#include "Player.h"



Player::Player() :body(sf::Vector2f(50,100))
{
	
}

sf::Vector2f Player::center()
{

	return sf::Vector2f(body.getPosition().x + (body.getSize().x/2), body.getPosition().y + (body.getSize().y/2));
}

void Player::setTexture(sf::Texture& tex)
{
	body.setTexture(&tex);
}

void Player::move(float x, float y)
{
	body.move(x, y);
}

void Player::setPos(float x, float y)
{
	body.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Player::getSize()
{
	return body.getSize();
}

sf::Vector2f Player::getPos()
{
	return body.getPosition();
}

void Player::draw(sf::RenderTarget & w, sf::RenderStates SplashStates) const
{
	w.draw(body);
}

sf::FloatRect Player::globalBounds()
{
	return body.getGlobalBounds();
}