#ifndef	_MENU_H
#define _MENU_H

//include
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "InputManager.h"
#include "AudioManager.h"

class Menu {
private:
	enum ColorPresets { PRESETONE, PRESETTWO };
	ColorPresets preset;
	std::vector<sf::Texture> textures;
	std::vector<std::pair<sf::Sprite, bool>> sprites;/*The sprite will store each sprite for the menu,
													 the bool will be used to check witch option is selected.*/
	sf::Texture arrowHeadTexture; //Used to point to the option the player has highlighted.
	sf::Sprite arrowHeadSprite;
	
public:
	int currentLevel; //The current level selected to Play. Read by game class when gameOn == true to create the approprate level. 
	bool showSettings, gameOn, Exit, showExitConfermation, ShowLevelsSelect;
	Menu(std::pair<float, float> windowDesmentions);
	~Menu();
	void Update();
	void Draw(sf::RenderWindow &w);
};
#endif