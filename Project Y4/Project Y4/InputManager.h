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
	std::vector<sf::String> keysPressedLastUpdate;
	static InputManager* mInstance;
	InputManager();

public:
	static InputManager* instance();
	std::vector<sf::String> const& getKeys();
	std::vector<sf::String> const& getKeysLastUpdate();
	bool Down(sf::String key);
	bool Up(sf::String key);
	bool Pressed(sf::String key);
	bool Held(sf::String key);
	bool Released(sf::String key);
	void UpdatePressedKeys(sf::Event e);
	void KeyPressEvent(sf::Event e);
	void KeyReleaseEvent(sf::Event e);
};
#endif
