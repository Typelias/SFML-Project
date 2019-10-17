#include "Door.h"
#include <iostream>

Door::Door(GameDataRef data, bool open) : _data(data), isOpen(open)
{
	sideA.setFillColor(sf::Color::Color(125, 125, 125));
	sideB.setFillColor(sf::Color::Color(125, 125, 125));
}

sf::FloatRect Door::sideABounds()
{
	return sideA.getGlobalBounds();
}

sf::FloatRect Door::sideBBounds()
{
	return sideB.getGlobalBounds();
}

sf::Vector2f Door::sideAPos()
{
	return sideA.getPosition();
}

sf::Vector2f Door::sideBPos()
{
	return sideB.getPosition();
}

void Door::open()
{
	switch (type)
	{
	case 'T':
		sideA.move(-10.f, 0);
		sideB.move(10.f, 0);
		break;
	case 'B':
		sideA.move(-10.f, 0);
		sideB.move(10.f, 0);
		break;
	case 'L':
		sideA.move(0.f, -10.f);
		sideB.move(0.f, 10.f);
		break;
	case 'R':
		sideA.move(0.f, -10.f);
		sideB.move(0.f, 10.f);
		break;
	default:
		std::cout << "error\n";
		break;

	}
}

void Door::close()
{
	switch (type)
	{
	case 'T':
		sideA.move(10.f, 0);
		sideB.move(-10.f, 0);
		break;
	case 'B':
		sideA.move(10.f, 0);
		sideB.move(-10.f, 0);
		break;
	case 'L':
		sideA.move(0.f, 10.f);
		sideB.move(0.f, -10.f);
		break;
	case 'R':
		sideA.move(0.f, 10.f);
		sideB.move(0.f, -10.f);
		break;
	default:
		std::cout << "error\n";
		break;

	}
}

void Door::draw(sf::RenderTarget & w, sf::RenderStates SplashStates) const
{
	w.draw(sideA);
	w.draw(sideB);
}

void Door::makeTop()
{
	type = 'T';
	if (isOpen)
	{
		sideA.setSize(sf::Vector2f(_data->window.getSize().x / 2.f, Wall_THICKNESS));
		sideA.setPosition(sf::Vector2f(-Player_WIDTH, 0.f));

		sideB.setSize(sf::Vector2f(_data->window.getSize().x / 2.f, Wall_THICKNESS));
		sideB.setPosition(sf::Vector2f(_data->window.getSize().x / 2.f + Player_WIDTH, 0.f));
	}
	else
	{
		sideA.setSize(sf::Vector2f(_data->window.getSize().x / 2.f, Wall_THICKNESS));
		sideA.setPosition(sf::Vector2f(0.f, 0.f));

		sideB.setSize(sf::Vector2f(_data->window.getSize().x / 2.f, Wall_THICKNESS));
		sideB.setPosition(sf::Vector2f(_data->window.getSize().x / 2.f, 0.f));
	}
	
}

void Door::makeBot()
{
	type = 'B';
	if (isOpen)
	{
		sideA.setSize(sf::Vector2f(_data->window.getSize().x / 2.f, Wall_THICKNESS));
		sideA.setPosition(sf::Vector2f(-Player_WIDTH, _data->window.getSize().y - Wall_THICKNESS));
		
		sideB.setSize(sf::Vector2f(_data->window.getSize().x / 2.f, Wall_THICKNESS));
		sideB.setPosition(sf::Vector2f(_data->window.getSize().x / 2.f + Player_WIDTH, _data->window.getSize().y - Wall_THICKNESS));
	}
	else
	{
		sideA.setSize(sf::Vector2f(_data->window.getSize().x / 2.f, Wall_THICKNESS));
		sideA.setPosition(sf::Vector2f(0.f, _data->window.getSize().y - Wall_THICKNESS));

		sideB.setSize(sf::Vector2f(_data->window.getSize().x / 2.f, Wall_THICKNESS));
		sideB.setPosition(sf::Vector2f(_data->window.getSize().x / 2.f, _data->window.getSize().y - Wall_THICKNESS));
	}
}

void Door::makeRight()
{
	type = 'R';
	if (isOpen)
	{
		sideA.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y / 2.f));
		sideA.setPosition(sf::Vector2f(_data->window.getSize().x - Wall_THICKNESS, -Player_HIGHT));

		sideB.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y / 2.f));
		sideB.setPosition(sf::Vector2f(_data->window.getSize().x - Wall_THICKNESS, _data->window.getSize().y / 2.f + Player_HIGHT));
	}
	else
	{
		sideA.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y / 2.f));
		sideA.setPosition(sf::Vector2f(_data->window.getSize().x - Wall_THICKNESS, 0.f));

		sideB.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y / 2.f));
		sideB.setPosition(sf::Vector2f(_data->window.getSize().x - Wall_THICKNESS, _data->window.getSize().y / 2.f));
	}
}

void Door::makeLeft()
{
	type = 'L';
	if (isOpen)
	{
		sideA.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y / 2.f));
		sideA.setPosition(sf::Vector2f(0.f, -Player_HIGHT));

		sideB.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y / 2.f));
		sideB.setPosition(sf::Vector2f(0.f, _data->window.getSize().y / 2.f + Player_HIGHT));
	}
	else
	{
		sideA.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y / 2.f));
		sideA.setPosition(sf::Vector2f(0.f,0.f));

		sideB.setSize(sf::Vector2f(Wall_THICKNESS, _data->window.getSize().y / 2.f));
		sideB.setPosition(sf::Vector2f(0.f, _data->window.getSize().y / 2.f));
	}
}
