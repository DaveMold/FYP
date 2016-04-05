#ifndef LEVELELEMENT_H
#define LEVELELEMENT_H
#include "MenuElement.h"
#include "json.h"
#include <fstream>


class LevelElement : public MenuElement {
public:
	LevelElement(sf::Vector2f pos,int levelID, sf::String string, bool draw, std::function<void(sf::String)> function);
	~LevelElement();
	void ReadLevelData();
	void UpdateLevelTime();
	void Select() override;
	void Draw(sf::RenderWindow &w) override;
private:
	std::function<void(sf::String)> funct_;
	float time_, levelID_;
	sf::Text levelTimeText_;
};
#endif