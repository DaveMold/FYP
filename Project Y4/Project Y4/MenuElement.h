#ifndef	_MENUELEMENT_H
#define _MENUELEMENT_H

//include
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <functional>
#include <iostream>

class MenuElement {
private:
	bool active_;//is this the selected menu element.
	std::pair<MenuElement*, MenuElement*> next_prev_;//Stores the last menu element and the next element.
	std::function< void() > funct_;
public:
	sf::Text text_;
	bool draw_;//if false dont render.
	sf::Font font_;
	MenuElement(sf::Vector2f pos, sf::String string, bool draw, MenuElement* next, MenuElement* previous, std::function<void()> function);
	MenuElement(sf::Vector2f pos, sf::String string, bool draw, std::function<void ()> function);
	MenuElement(sf::Vector2f pos, sf::String string, bool draw);
	~MenuElement();
	sf::Vector2f GetPos();
	void SetNext(MenuElement* next);
	void SetPrev(MenuElement* prev);
	void ToggleDraw(); // toggles a bool to tell if the element should be rendered to the screen.
	void SetDraw(bool d); // sets the bool to tell if the element should be rendered to the screen.
	virtual void Select();
	MenuElement* Next();
	MenuElement* Previous();
	virtual void Draw(sf::RenderWindow &w);
};
#endif