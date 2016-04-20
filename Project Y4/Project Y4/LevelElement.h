#ifndef LEVELELEMENT_H
#define LEVELELEMENT_H
#include "MenuElement.h"
#include "json.h"
#include <fstream>


class LevelElement : public MenuElement {
public:
	LevelElement(sf::Vector2f pos,int levelID, sf::String string, bool draw, std::function<void(sf::String)> function); //consturctor for setting pos, the string and what level it should refer too and the store of the function pointer
	~LevelElement(); //deconstructor
	void ReadLevelData(); //Reads the level time from the save file using Json.
	void UpdateLevelTime(); //Updates the level time to show with the menu element.
	void Select() override; //an override of the select function to take the level valuse in the function.
	void Draw(sf::RenderWindow &w) override; //draws the element id draw is set to true.
private:
	std::function<void(sf::String)> funct_; //stores the function pointer that will except a string for an arument.
	float time_; //stores the time for the level.
	int levelID_; //store the level id for collecting data.
	sf::Text levelTimeText_; //displaies the level time.
};
#endif