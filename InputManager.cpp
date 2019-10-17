#include "InputManager.h"


bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (tempRect.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}

	}

	return false;
}

sf::Vector2f InputManager::GetMousePos(sf::RenderWindow & window)
{
	return sf::Vector2f(sf::Mouse::getPosition(window));
}

bool InputManager::keyIn(sf::Keyboard::Key button)
{
	if (sf::Keyboard::isKeyPressed(button))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputManager::mouseClick(sf::Mouse::Button button)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		return true;
	}
	else
	{
		return false;
	}
}

