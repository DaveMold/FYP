#include "InputManager.h"


InputManager* InputManager::mInstance = nullptr;
InputManager::InputManager() {

}

InputManager* InputManager::instance() {
	if (mInstance == nullptr)
	{
		mInstance = new InputManager();
	}

	return mInstance;
}


std::vector<sf::String> const& InputManager::getKeys() {
	return keysPressed;
}

void InputManager::UpdatePressedKeys(sf::Event e) {
	keysPressed.clear();
	if (e.type == sf::Event::EventType::KeyPressed)
	{
		switch (e.key.code)
		{
		case sf::Keyboard::Left:
			std::cout << "Left" << std::endl;
			keysPressed.push_back("Left");
			break;
		case sf::Keyboard::Right:
			std::cout << "Right" << std::endl;
			keysPressed.push_back("Right");
			break;
		case sf::Keyboard::Up:
			keysPressed.push_back("Up");
			break;
		default:
			break;
		}
	}
	else if (sf::Event::TextEntered == sf::Event::EventType::KeyPressed)
	{
		std::cout << e.key.code << std::endl;
		switch (e.key.code)
		{
		case sf::Keyboard::G:
			std::cout << "Gravity On/Off" << std::endl;
			keysPressed.push_back("G");
			break;
		default:
			break;
		}
	}
	
}