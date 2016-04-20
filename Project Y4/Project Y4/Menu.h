#ifndef	_MENU_H
#define _MENU_H

//include
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
#include <iostream>
#include <functional>
#include "json.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "MenuElement.h"
#include "LevelElement.h"

class Menu {
private:
	std::vector<MenuElement*> elements_; //stores the menu elements for the menu.
	MenuElement* curretElement_; //stores a pointer to the current element.
	sf::Texture arrowHeadTexture_; //Used to point to the option the player has highlighted.
	sf::Sprite arrowHeadSprite_; //The arrow head is used to point to the current element.
	
public:
	enum ColorPresets { PRESETONE, PRESETTWO }; //Used to identify which color preset is active.
	ColorPresets preset_; //stores the current color preset selected.
	int currentLevel; //The current level selected to Play. Read by game class when gameOn == true to create the approprate level. 
	bool showSettings_, gameOn_, exit_, showExitConfermation_, ShowLevelsSelect_; //bools are used to tell when diferent parts of the level should be rendered.
	Menu(std::pair<float, float> windowDesmentions); //constructor for the menu that will set all the menu elements with there function pointer and lables.
	~Menu(); //deconstructor.
	void Update(); //quires the inputmanager and either sets next/previous of the current element to the current element. or calls select of the element to run their functional pointer.
	void ToggleSettings(); //Toggles the draw of the settings.
	void ToggleExitConfermation(); //toggles the exit confermation(eg YES, NO).
	void ToggleLevelSelect(); //toggles the level select draw.
	void SetLevel(sf::String s); //sets the current level depending on the lable used by the menu level element.
	void ToggleStartGame(); //Toggle weater the game will start or not.
	void ToggleExit(); //Toggles the draw of the exit confermation.
	void ResetSelect(); //Resets the menu so only the base menu draws and the current element is set to the first element.
	void ToggleColorPreset(); //Toggles the draw of the color Preset.
	void Draw(sf::RenderWindow &w); //sets the arrow head to point to the current element. also draws all elements thats have draw set to true.
};
#endif