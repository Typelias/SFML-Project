#include "Room2.h"
#include <iostream>
#include "DeathState.h"
#include "Room3.h"

Room2::Room2(GameDataRef data) : _data(data), leftWall(data), topWall(data), bottomDoor(data, true), rightDoor(data, false) {}

void Room2::Init()
{
	start = std::chrono::high_resolution_clock::now();
	timer = 0;

	leftWall.setLeft();
	topWall.setTop();
	bottomDoor.makeBot();
	rightDoor.makeRight();

	//Loading and applying Enemy texture
	e1.setTexture(_data->assets.GetTexture("Enemy"));

	//Defining Enemy bullets
	b2 = Bullet(10.f, true);

	//Setting Enemy position and adding them to vector
	e1.setPos(sf::Vector2f(Wall_THICKNESS + 50.f, Wall_THICKNESS + 50.f));
	enemies.push_back(e1);
	e1.setPos(sf::Vector2f(_data->window.getSize().x - Wall_THICKNESS - 50.f -e1.getSize().x, Wall_THICKNESS + 50.f));
	enemies.push_back(e1);

	//Setting Player texture and setting his position
	p1.setTexture(_data->assets.GetTexture("PlayerTexture"));
	p1.setPos(_data->window.getSize().x / 2.f - (p1.getSize().x / 2.f), _data->window.getSize().y - p1.getSize().y);

	//Adding Walls to vector
	Walls.push_back(&leftWall);
	Walls.push_back(&topWall);
	doors.push_back(&bottomDoor);
	doors.push_back(&rightDoor);



}

void Room2::HandleInput()
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

void Room2::Update(float dt)
{
	timer++;
	
	//Player keyIn
	if (_data->input.keyIn(sf::Keyboard::A) && canMove(p1, leftWall.globalBounds()) && canMove(p1, bottomDoor.sideABounds()))
		p1.move(-10.f, 0.f);
	if (_data->input.keyIn(sf::Keyboard::D) && canMove(p1, rightDoor.sideABounds()) && canMove(p1,rightDoor.sideBBounds()) && canMove(p1, bottomDoor.sideBBounds()))
		p1.move(10.f, 0.f);
	if (_data->input.keyIn(sf::Keyboard::W) && canMove(p1, topWall.globalBounds()) && canMove(p1, rightDoor.sideABounds()))
		p1.move(0.f, -10.f);
	if (_data->input.keyIn(sf::Keyboard::S) && canMove(p1, bottomDoor.sideABounds()) && canMove(p1, bottomDoor.sideBBounds()) && canMove(p1, rightDoor.sideBBounds()))
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


	for(int i = 0; i < bullets.size(); i++)
	{
		Bullet & e = bullets[i];
		e.moveForvard();
		if (e.travel >= 100)
		{
			bullets.erase(bullets.begin() + i);
		}
		else
		{
			e.travel++;
		}
		//i++;

		//Checking if Player is hit
		if (e.globalBounds().intersects(p1.globalBounds()) && e.isEnemy())
		{
			std::cout << "dead" << std::endl;
			_data->machine.AddState(StateRef(new DeathState(_data)));
		}

		//Checking if enemies are hit
		for(int y = 0; y< enemies.size(); y++)
		{
			Enemy & f = enemies[y];
			if (e.globalBounds().intersects(f.globalBounds()) && !e.isEnemy())
			{
				enemies.erase(enemies.begin() + y);
			}
		}
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


	if (p1.getPos().y + p1.getSize().y < _data->window.getSize().y - Wall_THICKNESS && bottomDoor.sideAPos().x <= 0)
	{
		std::cout << "Close door" << std::endl;
		bottomDoor.close();
	}

	if (enemies.empty() && rightDoor.sideAPos().y>-p1.getSize().y)
	{
		std::cout << "Open door" << std::endl;
		rightDoor.open();

	}

	if (p1.getPos().x > _data->window.getSize().x + p1.getSize().x)
	{
		stop = std::chrono::high_resolution_clock::now();
		elapsedTime = stop - start;
		_data->addTime(elapsedTime);
		_data->machine.AddState(StateRef(new Room3(_data)));
	}

	if (_data->input.keyIn(sf::Keyboard::R))
	{
		_data->machine.AddState(StateRef(new Room1(_data)));
	}
}

void Room2::Draw(float dt)
{
	_data->window.clear(sf::Color::White);

	auto drawRef = [&](sf::Drawable & d)
	{
		_data->window.draw(d);
	};

	auto drawPoint = [&](sf::Drawable * d)
	{
		_data->window.draw(*d);
	};

	std::for_each(Walls.begin(), Walls.end(), drawPoint);

	drawRef(p1);

	std::for_each(enemies.begin(), enemies.end(), drawRef);

	std::for_each(bullets.begin(), bullets.end(), drawRef);
	
	std::for_each(doors.begin(), doors.end(), drawPoint);


	_data->window.display();
}

bool Room2::canMove(Player p, sf::FloatRect rect)
{
	if (p.globalBounds().intersects(rect))
	{
		return false;
	}


	return true;
}
