#include "InputManager.h"


InputManager* InputManager::mInstance = nullptr;
InputManager::InputManager() {
	keysPressed = std::vector<sf::String>();
	keysPressedLastUpdate = std::vector<sf::String>();
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

std::vector<sf::String> const& InputManager::getKeysLastUpdate() {
	return keysPressedLastUpdate;
}

bool InputManager::Down(sf::String key) {
	auto begin = keysPressed.begin();
	auto end = keysPressed.end();
	if (std::find(begin, end, key) != end)
		return true;
	return false;
}

bool InputManager::Up(sf::String key) {
	auto begin = keysPressed.begin();
	auto end = keysPressed.end();
	if (std::find(begin, end, key) == end)
		return true;
	return false;
}

bool InputManager::Pressed(sf::String key){
	auto begin = keysPressed.begin();
	auto end = keysPressed.end();
	auto begin_LU = keysPressedLastUpdate.begin();
	auto end_LU = keysPressedLastUpdate.end();
	if (std::find(begin_LU, end_LU, key) != end_LU && std::find(begin, end, key) != end)
		return true;
	return false;
}

bool InputManager::Held(sf::String key) {
	auto begin = keysPressed.begin();
	auto end = keysPressed.end();
	auto begin_LU = keysPressedLastUpdate.begin();
	auto end_LU = keysPressedLastUpdate.end();
	if (std::find(begin_LU, end_LU, key) != end_LU && std::find(begin, end, key) != end)
	{
		//keysPressedLastUpdate.erase(std::remove(keysPressedLastUpdate.begin(), keysPressedLastUpdate.end(), key), keysPressedLastUpdate.end());
		return true;
	}
	return false;
}

bool InputManager::Released(sf::String key) {
	auto begin = keysPressed.begin();
	auto end = keysPressed.end();
	auto begin_LU = keysPressedLastUpdate.begin();
	auto end_LU = keysPressedLastUpdate.end();
	if (std::find(begin_LU, end_LU, key) != end_LU && std::find(begin, end, key) == end)
	{
		keysPressedLastUpdate.erase(std::remove(keysPressedLastUpdate.begin(), keysPressedLastUpdate.end(), key), keysPressedLastUpdate.end());
		return true;
	}
	return false;
}

void InputManager::KeyPressEvent(sf::Event e) {
	
	if (e.type == sf::Event::EventType::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Left)
		{
			if (keysPressed.end() == std::find(keysPressed.begin(), keysPressed.end(), "Left"))
			{
				keysPressed.push_back("Left");
			}
		}
		if (e.key.code == sf::Keyboard::Right)
		{
			if (keysPressed.end() == std::find(keysPressed.begin(), keysPressed.end(), "Right"))
			{
				keysPressed.push_back("Right");
			}
		}
		if (e.key.code == sf::Keyboard::Up)
		{
			if (keysPressed.end() == std::find(keysPressed.begin(), keysPressed.end(), "Up"))
			{
				keysPressed.push_back("Up");
			}
		}
		if (e.key.code == sf::Keyboard::Down)
		{
			if (keysPressed.end() == std::find(keysPressed.begin(), keysPressed.end(), "Down"))
			{
				keysPressed.push_back("Down");
			}
		}
		if (e.key.code == sf::Keyboard::End)
		{
			if(keysPressed.end() == std::find(keysPressed.begin(), keysPressed.end(), "End"))
				keysPressed.push_back("End");
		}
		if (e.key.code == sf::Keyboard::Delete)
		{
			if (keysPressed.end() == std::find(keysPressed.begin(), keysPressed.end(), "Delete"))
				keysPressed.push_back("Delete");
		}
		if (e.key.code == sf::Keyboard::Home)
		{
			if (keysPressed.end() == std::find(keysPressed.begin(), keysPressed.end(), "Home"))
				keysPressed.push_back("Home");
		}
		if (e.key.code == sf::Keyboard::G)
		{
			if (keysPressed.end() == std::find(keysPressed.begin(), keysPressed.end(), "G"))
				keysPressed.push_back("G");
		}
		
		keysPressedLastUpdate = keysPressed;
	}
}

void InputManager::KeyReleaseEvent(sf::Event e) {
	
	if (e.type == sf::Event::EventType::KeyReleased)
	{
		std::vector<sf::String> removeKeyVec;
		if (e.key.code == sf::Keyboard::Up)
		{
			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				if ((*itr) == "Up")
				{
					removeKeyVec.push_back(*itr);
				}
			}
		}
		if (e.key.code == sf::Keyboard::Right)
		{
			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				if ((*itr) == "Right")
				{
					removeKeyVec.push_back(*itr);
				}
			}
		}
		if (e.key.code == sf::Keyboard::Left)
		{
			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				if ((*itr) == "Left")
				{
					removeKeyVec.push_back(*itr);
				}
			}
		}
		if (e.key.code == sf::Keyboard::Down)
		{
			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				if ((*itr) == "Down")
				{
					removeKeyVec.push_back(*itr);
				}
			}
		}
		if (e.key.code == sf::Keyboard::End)
		{
			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				if ((*itr) == "End")
				{
					removeKeyVec.push_back(*itr);
				}
			}
		}
		if (e.key.code == sf::Keyboard::Delete)
		{
			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				if ((*itr) == "Delete")
				{
					removeKeyVec.push_back(*itr);
				}
			}
		}
		if (e.key.code == sf::Keyboard::Home)
		{
			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				if ((*itr) == "Home")
				{
					removeKeyVec.push_back(*itr);
				}
			}
		}
		if (e.key.code == sf::Keyboard::G)
		{
			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				if ((*itr) == "G")
				{
					removeKeyVec.push_back(*itr);
				}
			}
		}
		for (auto indexItr = removeKeyVec.begin(); indexItr != removeKeyVec.end(); indexItr++) {
			//remove all elements with the value indexItr.
			keysPressed.erase(std::remove(keysPressed.begin(), keysPressed.end(), (*indexItr)), keysPressed.end());
		}
		removeKeyVec.clear();

	}
}