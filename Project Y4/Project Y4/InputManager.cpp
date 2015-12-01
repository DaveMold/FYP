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
		if (e.key.code == sf::Keyboard::Left)
		{
			keysPressed.push_back("Left");
		}
		if (e.key.code == sf::Keyboard::Right)
		{
			keysPressed.push_back("Right");
		}
		if (e.key.code == sf::Keyboard::Up)
		{
			keysPressed.push_back("Up");
		}
		if (e.key.code == sf::Keyboard::End)
		{
			keysPressed.push_back("End");
		}
		if (e.key.code == sf::Keyboard::Home)
		{
			keysPressed.push_back("Home");
		}
		if (e.key.code == sf::Keyboard::G)
		{
			std::cout << "Gravity On/Off" << std::endl;
			keysPressed.push_back("G");
		}
	}
	/*if (e.type == sf::Event::EventType::KeyReleased)
	{
		if (e.key.code == sf::Keyboard::Up)
		{
			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				if ((*itr) == "Up")
					keysPressed.erase(itr);
			}
		}
	}*/
	/*else if (sf::Event::TextEntered == sf::Event::EventType::KeyPressed)
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
	}*/
	
}