#pragma once
#include <SFML/Graphics.hpp>
/*!
	InputManager is used to handle specific input type
*/
class InputManager
{
public:
	//! The constructor for the InputManager class
	InputManager() {};
	//! The destructor for the InputManager class
	~InputManager() {};
	//! This function is used to check if a sprite has been clicked
	bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
	//! This function is used to get the mouse position in the game window
	sf::Vector2f GetMousePos(sf::RenderWindow &window);
	//! This function is used to se if a provided button is pressed
	bool keyIn(sf::Keyboard::Key button);
	//! This function is used to se if the provided mouse button has been pressed
	bool mouseClick(sf::Mouse::Button button);
};




