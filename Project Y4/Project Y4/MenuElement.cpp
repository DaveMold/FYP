#include "MenuElement.h"

MenuElement::MenuElement(sf::Vector2f pos, sf::String string, bool draw, MenuElement* next, MenuElement* previous, std::function<void ()> function)
	: draw_(draw), funct_(function) {
	next_prev_.first = next;
	next_prev_.second = previous;
	font_.loadFromFile("Assets/Menu/Squared Display.ttf");
	text_.setFont(font_);
	text_.setPosition(pos);
	text_.setString(string);
	text_.setColor(sf::Color::Blue);
	text_.setCharacterSize(32);
	text_.setStyle(sf::Text::Bold);
}

MenuElement::MenuElement(sf::Vector2f pos, sf::String string, bool draw, std::function<void ()> function)
	: draw_(draw), funct_(function) {
	font_.loadFromFile("Assets/Menu/Squared Display.ttf");
	text_.setFont(font_);
	text_.setPosition(pos);
	text_.setString(string);
	text_.setColor(sf::Color::Blue);
	text_.setCharacterSize(32);
	text_.setStyle(sf::Text::Bold);
}

MenuElement::MenuElement(sf::Vector2f pos, sf::String string, float f_size, bool draw, std::function<void()> function)
	: draw_(draw), funct_(function) {
	font_.loadFromFile("Assets/Menu/Squared Display.ttf");
	text_.setFont(font_);
	text_.setScale(f_size, f_size);
	text_.setPosition(pos);
	text_.setString(string);
	text_.setColor(sf::Color::Blue);
	text_.setCharacterSize(32);
	text_.setStyle(sf::Text::Bold);
}

MenuElement::MenuElement(sf::Vector2f pos, sf::String string, bool draw)
	: draw_(draw) {
	font_.loadFromFile("Assets/Menu/Squared Display.ttf");
	text_.setFont(font_);
	text_.setPosition(pos);
	text_.setString(string);
	text_.setColor(sf::Color::Blue);
	text_.setCharacterSize(32);
	text_.setStyle(sf::Text::Bold);
}

MenuElement::~MenuElement() {

}

sf::Vector2f MenuElement::GetPos() {
	return text_.getPosition();
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

void MenuElement::SetDraw(bool v) {
	draw_ = v;
}

MenuElement* MenuElement::Next() {
	return next_prev_.first;
}

MenuElement* MenuElement::Previous() {
	return next_prev_.second;
}

void MenuElement::Draw(sf::RenderWindow &w) {
	if(draw_)
		w.draw(text_);
}