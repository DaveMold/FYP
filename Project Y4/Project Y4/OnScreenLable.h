#ifndef	_ONSCREENLABLE_H
#define _ONSCREENLABLE_H

//include
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <functional>
#include <iostream>

class OnScreenLable {
private:
	sf::Font font_;
	bool draw_;//if false dont render.
public:
	sf::Text text_;
	OnScreenLable(sf::Vector2f pos, sf::String string, bool draw);
	~OnScreenLable();
	void SetText(sf::String s);
	void SetPos(sf::Vector2f p);
	sf::Vector2f GetPos();
	void ToggleDraw(); // toggles a bool to tell if the element should be rendered to the screen.
	void SetDraw(bool d); // sets the bool to tell if the element should be rendered to the screen.
	void Draw(sf::RenderWindow &w);
};
#endif