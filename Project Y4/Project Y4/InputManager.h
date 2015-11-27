#ifndef _InputManager_
#define _InputManager_

//includes
#include <vector>
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"


class InputManager {
private:
	std::vector<sf::String> keysPressed;
	static InputManager* mInstance;
	InputManager();

public:
	static InputManager* instance();
	std::vector<sf::String> const& getKeys();
	void UpdatePressedKeys(sf::Event e);
};
#endif
