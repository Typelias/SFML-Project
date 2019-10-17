#include "Wall.h"

Wall::Wall(GameDataRef data) : _data(data)
{
	body.setFillColor(sf::Color::Color(125, 125, 125));
}



sf::Vector2f Wall::getPos()
{
	return body.getPosition();
}

sf::FloatRect Wall::globalBounds()
{
	return body.getGlobalBounds();
}

void Wall::draw(sf::RenderTarget & w, sf::RenderStates SplashStates) const
{
	w.draw(body);
}

void Wall::setRight()
{
	body.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y));
	body.setPosition(sf::Vector2f(_data->window.getSize().x - Wall_THICKNESS, 0.f));
}

void Wall::setLeft()
{
	body.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y));
	body.setPosition(sf::Vector2f(0.f, 0.f));
}

void Wall::setTop()
{
	body.setSize(sf::Vector2f(_data->window.getSize().x, Wall_THICKNESS));
	body.setPosition(sf::Vector2f(0.f, 0.f));
}

void Wall::setBot()
{
	body.setSize(sf::Vector2f(_data->window.getSize().x, Wall_THICKNESS));
	body.setPosition(sf::Vector2f(0.f, _data->window.getSize().y - Wall_THICKNESS));
}

