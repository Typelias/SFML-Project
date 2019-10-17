#include "Room1.h"
#include <iostream>
#include "Room2.h"




Room1::Room1(GameDataRef data) : _data(data),topDoor(data,true),leftWall(data),rightWall(data),bottomWall(data) {}

void Room1::Init()
{
	_data->zeroTime();
	//Start timer for clock
	start = std::chrono::high_resolution_clock::now();
	topDoor.makeTop();
	leftWall.setLeft();
	rightWall.setRight();
	bottomWall.setBot();

	Walls.push_back(leftWall);
	Walls.push_back(bottomWall);
	Walls.push_back(rightWall);

	p1.setTexture(_data->assets.GetTexture("PlayerTexture"));
	p1.setPos(_data->window.getSize().x / 2.f - (p1.getSize().x / 2.f), _data->window.getSize().y - p1.getSize().y - Wall_THICKNESS);


}

void Room1::HandleInput()
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

void Room1::Update(float dt)
{

	//Player keyIn
	if (_data->input.keyIn(sf::Keyboard::A) && canMove(p1,leftWall.globalBounds()) && canMove(p1,topDoor.sideABounds()))
		p1.move(-10.f, 0.f);
	if (_data->input.keyIn(sf::Keyboard::D) && canMove(p1, rightWall.globalBounds()) && canMove(p1, topDoor.sideBBounds()))
		p1.move(10.f, 0.f);
	if (_data->input.keyIn(sf::Keyboard::W) && canMove(p1, topDoor.sideABounds()) && canMove(p1, topDoor.sideBBounds()))
		p1.move(0.f, -10.f);
	if (_data->input.keyIn(sf::Keyboard::S) && canMove(p1,bottomWall.globalBounds()))
		p1.move(0.f, 10.f);

	//Shooting
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
		Bullet &e = bullets[i];
		e.moveForvard();
		if (e.travel >= 100)
		{
			bullets.erase(bullets.begin() + i);
		}
		else
		{
			e.travel++;
		}
	}

	//Next room
	if (p1.getPos().y < -p1.getSize().y)
	{
		stop = std::chrono::high_resolution_clock::now();
		elapsedTime = stop - start;
		_data->addTime(elapsedTime);
		_data->machine.AddState(StateRef(new Room2(_data)));
	}

	if (_data->input.keyIn(sf::Keyboard::R))
	{
		_data->machine.AddState(StateRef(new Room1(_data))); 
	}


}

void Room1::Draw(float dt)
{
	_data->window.clear(sf::Color::Green);

	auto drawRef = [&](sf::Drawable & d)
	{
		_data->window.draw(d);
	};

	drawRef(p1);

	std::for_each(bullets.begin(), bullets.end(), drawRef);

	std::for_each(Walls.begin(), Walls.end(), drawRef);
	drawRef(topDoor);
	

	_data->window.display();
}

bool Room1::canMove(Player p, sf::FloatRect rect)
{
	if (p.globalBounds().intersects(rect))
	{
		return false;
	}

	return true;

}
