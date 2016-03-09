#include "MenuElement.h"

MenuElement::MenuElement(sf::Vector2f pos, sf::String path, bool draw, MenuElement* next, MenuElement* previous, std::function<void *()> function)
	: draw_(draw), funct_(function) {
	next_prev_.first = next;
	next_prev_.second = previous;
	texture_.loadFromFile(path);
	sprite_.setTexture(texture_);
	sprite_.setPosition(pos);
}

MenuElement::MenuElement(sf::Vector2f pos, sf::String path, bool draw, std::function<void *()> function)
	: draw_(draw), funct_(function) {
	texture_.loadFromFile(path);
	sprite_.setTexture(texture_);
	sprite_.setPosition(pos);
}

MenuElement::~MenuElement() {

}

sf::Vector2f MenuElement::GetPos() {
	return sprite_.getPosition();
}

void MenuElement::Select() {
	funct_();
}

void MenuElement::SetNext(MenuElement* next) {
	next_prev_.first = next;
}

void MenuElement::SetPrev(MenuElement* prev) {
	next_prev_.second = prev;
}

void MenuElement::ToggleDraw() {
	switch (draw_)
	{
	case true:
		draw_ = false;
		break;
	case false:
		draw_ = true;
		break;
	default:
		printf("MenuElement::ToggleDraw - draw_ not valid.\n");
		break;
	}
}

MenuElement* MenuElement::Next() {
	return next_prev_.first;
}

MenuElement* MenuElement::Previous() {
	return next_prev_.second;
}

void MenuElement::Draw(sf::RenderWindow &w) {
	if(draw_)
		w.draw(sprite_);
}