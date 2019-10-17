#include "Room3.h"
#include <iostream>
#include "DeathState.h"
#include "Room4.h"

Room3::Room3(GameDataRef data):_data(data), topDoor(data, false), leftDoor(data, true), bottomWall(data), rightWall(data){}

void Room3::Init()
{
	start = std::chrono::high_resolution_clock::now();
	isShooting = false;
	timer = 0;
	e1.setTexture(_data->assets.GetTexture("Enemy"));

	topDoor.makeTop();
	leftDoor.makeLeft();
	bottomWall.setBot();
	rightWall.setRight();

	b2 = Bullet(10.f, true);

	p1.setPos(0, _data->window.getSize().y / 2 - p1.getSize().y / 2);
	p1.setTexture(_data->assets.GetTexture("PlayerTexture"));

	Walls.push_back(&rightWall);
	Walls.push_back(&bottomWall);
	doors.push_back(&topDoor);
	doors.push_back(&leftDoor);
	

	//Setting Enemy positions
	e1.setPos(sf::Vector2f(_data->window.getSize().x - Wall_THICKNESS - e1.getSize().x - 10.f, Wall_THICKNESS + 10.f));
	enemies.push_back(Enemy(e1));
	e1.setPos(sf::Vector2f(_data->window.getSize().x / 2.f - e1.getSize().x / 2, Wall_THICKNESS + 10.f));
	enemies.push_back(Enemy(e1));
	e1.setPos(sf::Vector2f(Wall_THICKNESS + 10.f, _data->window.getSize().y - Wall_THICKNESS - e1.getSize().y - 10.f));
	enemies.push_back(Enemy(e1));

}

void Room3::HandleInput()
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

void Room3::Update(float dt)
{
	//Enemy shooting timer increases
	timer++;

	//Player keyIn
	if (_data->input.keyIn(sf::Keyboard::A) && canMove(p1, leftDoor.sideABounds()) && canMove(p1, leftDoor.sideBBounds()) && canMove(p1, topDoor.sideABounds()))
		p1.move(-10.f, 0.f);
	if (_data->input.keyIn(sf::Keyboard::D) && canMove(p1, rightWall.globalBounds()))
		p1.move(10.f, 0.f);
	if (_data->input.keyIn(sf::Keyboard::W) && canMove(p1, topDoor.sideABounds()) && canMove(p1, topDoor.sideBBounds()) && canMove(p1,leftDoor.sideABounds()))
		p1.move(0.f, -10.f);
	if (_data->input.keyIn(sf::Keyboard::S) && canMove(p1, bottomWall.globalBounds()) && canMove(p1, leftDoor.sideBBounds()))
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

	//Enemy shooting
	if (timer >= 50)
	{
		std::for_each(enemies.begin(), enemies.end(), [&](Enemy &e)
		{
			b2.setPos(e.center());
			b2.calculateVel(e.center(), p1.center());
			bullets.push_back(Bullet (b2));
		});

		timer = 0;
	}

	//Bullet travel and collision
	for(int i = 0; i<bullets.size(); i++)
	{
		Bullet &b = bullets[i];
		//Moving bullet forvard
		b.moveForvard();
		//Check if bullet has traveld max distance
		if (b.travel >= 100)
		{
			bullets.erase(bullets.begin() + i);
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

		//Check if Player bullet hits enemies
		for(int y = 0; y < enemies.size(); y++)
		{
			Enemy &e = enemies[y];
			if (b.globalBounds().intersects(e.globalBounds()) && !b.isEnemy())
			{
				enemies.erase(enemies.begin() + y);
			}
		}

	}

	//Doors
	if (p1.getPos().x > Wall_THICKNESS && leftDoor.sideAPos().y < 0)
	{
		leftDoor.close();
	}
	if (enemies.empty() && topDoor.sideAPos().x > -p1.getSize().x)
	{
		topDoor.open();
	}

	if (p1.getPos().y <= -p1.getSize().y)
	{
		std::cout << "Next room" << std::endl;
		stop = std::chrono::high_resolution_clock::now();
		elapsedTime = stop - start;
		_data->addTime(elapsedTime);

		_data->machine.AddState(StateRef(new Room4(_data)));
	}

	if (_data->input.keyIn(sf::Keyboard::R))
	{
		_data->machine.AddState(StateRef(new Room1(_data)));
	}

}

void Room3::Draw(float dt)
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

	std::for_each(Walls.begin(), Walls.end(), drawPoint);
	std::for_each(doors.begin(), doors.end(), drawPoint);

	drawRef(p1);

	std::for_each(enemies.begin(), enemies.end(), drawRef);

	std::for_each(bullets.begin(), bullets.end(), drawRef);

	//Display
	_data->window.display();

}

bool Room3::canMove(Player p, sf::FloatRect rect)
{
	if (p.globalBounds().intersects(rect))
	{
		return false;
	}

	return true;
}
