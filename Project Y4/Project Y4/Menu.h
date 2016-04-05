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
	enum ColorPresets { PRESETONE, PRESETTWO };
	ColorPresets preset_;
	
	std::vector<MenuElement*> elements_;

	MenuElement* curretElement_;

	sf::Texture arrowHeadTexture_; //Used to point to the option the player has highlighted.
	sf::Sprite arrowHeadSprite_;
	
public:
	int currentLevel; //The current level selected to Play. Read by game class when gameOn == true to create the approprate level. 
	bool showSettings_, gameOn_, exit_, showExitConfermation_, ShowLevelsSelect_;
	Menu(std::pair<float, float> windowDesmentions);
	~Menu();
	void Update();
	void ToggleSettings();
	void ToggleExitConfermation();
	void ToggleLevelSelect();
	void SetLevel(sf::String s);
	void ToggleStartGame();
	void ToggleExit();
	void ResetSelect();
	void ToggleColorPreset();
	void SaveLevelData(int id, float time);
	void Draw(sf::RenderWindow &w);
};
#endif