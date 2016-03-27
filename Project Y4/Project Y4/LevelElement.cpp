#include "LevelElement.h"

LevelElement::LevelElement(sf::Vector2f pos, sf::String string, bool draw, std::function<void(sf::String)> function)
	:MenuElement(pos, string, draw){
	funct_ = function;
}

LevelElement::~LevelElement() {

}

void LevelElement::Select() {
	funct_(text_.getString());
}