#ifndef LEVELELEMENT_H
#define LEVELELEMENT_H
#include "MenuElement.h"


class LevelElement : public MenuElement {
public:
	LevelElement(sf::Vector2f pos, sf::String string, bool draw, std::function<void(sf::String)> function);
	~LevelElement();
	void Select() override;
private:
	std::function<void(sf::String)> funct_;
};
#endif