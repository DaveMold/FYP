#include "OnScreenLable.h"

OnScreenLable::OnScreenLable(sf::Vector2f pos, sf::String string, bool draw)
	: draw_(draw) {
	font_.loadFromFile("Assets/Menu/Squared Display.ttf");
	text_.setFont(font_);
	text_.setPosition(pos);
	text_.setString(string);
	text_.setColor(sf::Color::White);
	text_.setCharacterSize(20);
	text_.setStyle(sf::Text::Bold);
}

OnScreenLable::~OnScreenLable() {

}

void OnScreenLable::SetText(sf::String s) {
	text_.setString(s);
}

void OnScreenLable::SetPos(sf::Vector2f p) {
	text_.setPosition(p);
}


sf::Vector2f OnScreenLable::GetPos() {
	return text_.getPosition();
}

void OnScreenLable::ToggleDraw() {
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

void OnScreenLable::SetDraw(bool v) {
	draw_ = v;
}

void OnScreenLable::Draw(sf::RenderWindow &w) {
	if (draw_)
		w.draw(text_);
}