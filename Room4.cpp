#include "Room4.h"
#include "DeathState.h"
#include "EndState.h"
#include <iostream>

Room4::Room4(GameDataRef data) :_data(data), leftWall(data), rightWall(data), bottomDoor(data, true), topDoor(data, false) {}

void Room4::Init()
{
	start = std::chrono::high_resolution_clock::now();
	leftWall.setLeft();
	rightWall.setRight();
	topDoor.makeTop();
	bottomDoor.makeBot();

	//Varibles
	isShooting = false;
	timer = 0;
	hits = 0;

	b2 = Bullet(10.f, true);

	//Player
	p1.setTexture(_data->assets.GetTexture("PlayerTexture"));
	p1.setPos(_data->window.getSize().x / 2.f - p1.getSize().x / 2.f, _data->window.getSize().y - p1.getSize().y);

	//Boss
	boss.setPos(sf::Vector2f(_data->window.getSize().x / 2.f - boss.getSize().x / 2.f, Wall_THICKNESS * 2.f));
	boss.setTexture(_data->assets.GetTexture("boss"));

	//Draws
	draws.push_back(&leftWall);
	draws.push_back(&rightWall);
	draws.push_back(&topDoor);
	draws.push_back(&bottomDoor);
	draws.push_back(&p1);

}

void Room4::HandleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}
}

void Room4::Update(float dt)
{
	//Setting left and right
	left = sf::Vector2f(p1.center().x - _data->window.getSize().x / 3.f, p1.center().y);
	right = sf::Vector2f(p1.center().x + _data->window.getSize().x / 3.f, p1.center().y);

	//Enemy shooting timer increases
	timer++;

	if (_data->input.keyIn(sf::Keyboard::A) && canMove(p1, leftWall.globalBounds()) && canMove(p1, topDoor.sideABounds()) && canMove(p1, bottomDoor.sideABounds()))
		p1.move(-10.f, 0.f);
	if (_data->input.keyIn(sf::Keyboard::D) && canMove(p1, rightWall.globalBounds()) && canMove(p1, topDoor.sideBBounds()) && canMove(p1, bottomDoor.sideBBounds()))
		p1.move(10.f, 0.f);
	if (_data->input.keyIn(sf::Keyboard::W) && canMove(p1, topDoor.sideABounds()) && canMove(p1, topDoor.sideBBounds()))
		p1.move(0.f, -10.f);
	if (_data->input.keyIn(sf::Keyboard::S) && canMove(p1, bottomDoor.sideABounds()) && canMove(p1, bottomDoor.sideBBounds()))
		p1.move(0.f, 10.f);


	//Player shooting
	if (_data->input.mouseClick(sf::Mouse::Left) && !isShooting)
	{
		b1.setPos(p1.center());
		b1.calculateVel(p1.center(), _data->input.GetMousePos(_data->window));

		bullets.push_back(Bullet(b1));
		isShooting = true;
	}
	else if (!_data->input.mouseClick(sf::Mouse::Left))
	{
		isShooting = false;
	}

	//Boss shooting
	if (timer >= 50 && hits < 10)
	{
		b2.setPos(boss.center());
		b2.calculateVel(boss.center(), p1.center());
		bullets.push_back(Bullet(b2));
		b2.calculateVel(boss.center(), right);
		bullets.push_back(Bullet(b2));
		b2.calculateVel(boss.center(), left);
		bullets.push_back(Bullet(b2));

		timer = 0;
	}

	//Bullet travel and collision
	for (int i = 0; i < bullets.size(); i++)
	{
		Bullet & b = bullets[i];
		erasing = false;
		//Moving bullet forvard
		b.moveForvard();
		//Check if bullet has traveld max distance
		if (b.travel >= 100)
		{
			erasing = true;
			toErase.push_back(i);
		}
		else
		{
			b.travel++;
		}
		//Check if Enemy bullet hits Player
		if (b.globalBounds().intersects(p1.globalBounds()) && b.isEnemy())
		{
			std::cout << "dead" << std::endl;
			_data->machine.AddState(StateRef(new DeathState(_data)));
		}

		if (b.globalBounds().intersects(boss.globalBounds()) && !b.isEnemy() && !erasing)
		{
			std::cout << "hit" << std::endl;
			toErase.push_back(i);
			hits++;
		}

	}

	if (!toErase.empty())
	{
		bullets.erase(bullets.begin() + toErase.at(0));
	}
	toErase.clear();

	if (p1.getPos().y + p1.getSize().y < _data->window.getSize().y - Wall_THICKNESS && bottomDoor.sideAPos().x <= 0)
	{
		std::cout << "Close door" << std::endl;
		bottomDoor.close();
	}

	if (!(hits<10) && topDoor.sideAPos().x > -p1.getSize().x)
	{
		topDoor.open();
	}

	if (p1.getPos().y <= -p1.getSize().y)
	{
		if (setTime)
		{
			stop = std::chrono::high_resolution_clock::now();
			elapsedTime = stop - start;
			_data->addTime(elapsedTime);
			setTime = false;
			_data->machine.AddState(StateRef(new EndState(_data)));
		}

		std::cout << "End Game " << _data->getTime() << std::endl;
	}
	if (_data->input.keyIn(sf::Keyboard::R))
	{
		_data->machine.AddState(StateRef(new Room1(_data)));
	}

}

void Room4::Draw(float dt)
{
	//Clear
	_data->window.clear(sf::Color::White);

	//Draw
	auto drawRef = [&](sf::Drawable & d)
	{
		_data->window.draw(d);
	};

	auto drawPoint = [&](sf::Drawable * d)
	{
		_data->window.draw(*d);
	};

	std::for_each(draws.begin(), draws.end(), drawPoint);


	if (hits < 10)
		drawPoint(&boss);

	std::for_each(bullets.begin(), bullets.end(), drawRef);

	//Display
	_data->window.display();
}

bool Room4::canMove(Player p, sf::FloatRect rect)
{
	if (p.globalBounds().intersects(rect))
	{
		return false;
	}

	return true;
}
