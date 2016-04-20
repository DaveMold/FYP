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
	std::vector<sf::String> keysPressed; //stores the keys pressed.
	std::vector<sf::String> keysPressedLastUpdate;	//stores the keys pressed last update so we can tell if a key is held perhaps.
	static InputManager* mInstance; //used for creating an instance of the class so the object can be acessed from any where.
	InputManager(); //Constructor

public:
	static InputManager* instance(); //get the instance or create a new one if one dose not egsist.
	std::vector<sf::String> const& getKeys(); //reuturns the keys pressed.
	std::vector<sf::String> const& getKeysLastUpdate(); //returns the keys pressed last update.
	bool Down(sf::String key); //if the key is just pressed down.
	bool Up(sf::String key); //if the key is just released.
	bool Pressed(sf::String key); //if the key has be pressed and not held.
	bool Held(sf::String key); // if the key is held down.
	bool Released(sf::String key); //if the keys is released but not pressed resenly
	void KeyPressEvent(sf::Event e); // update keys pressed.
	void KeyReleaseEvent(sf::Event e); // update keys relased.
};
#endif
