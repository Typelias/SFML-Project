#include "Boss.h"

Boss::Boss(float h, float w, sf::Color color)
{
	body.setSize(sf::Vector2f(w, h));
	body.setFillColor(color);
}

void Boss::setPos(sf::Vector2f pos)
{
	body.setPosition(pos);
}

void Boss::draw(sf::RenderTarget & w, sf::RenderStates States) const
{
	w.draw(body);
}

sf::Vector2f Boss::getSize()
{
	return body.getSize();
}

sf::Vector2f Boss::center()
{
	return sf::Vector2f(body.getPosition().x + (body.getSize().x / 2), body.getPosition().y + (body.getSize().y / 2));
}

sf::FloatRect Boss::globalBounds()
{
	return body.getGlobalBounds();
}

void Boss::setTexture(sf::Texture & tex)
{
	body.setTexture(&tex);
}
