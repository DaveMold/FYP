#ifndef	_MENUELEMENT_H
#define _MENUELEMENT_H

//include
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <functional>
#include <iostream>

class MenuElement {
private:
	sf::Texture texture_;
	sf::Sprite sprite_;
	bool active_;//is this the selected menu element.
	bool draw_;//if false dont render.
	std::pair<MenuElement*, MenuElement*> next_prev_;//Stores the last menu element and the next element.
	std::function<void *()> funct_;
public:
	MenuElement(sf::Vector2f pos, sf::String path, bool draw, MenuElement* next, MenuElement* previous, std::function<void *()> function);
	MenuElement(sf::Vector2f pos, sf::String path, bool draw, std::function<void *()> function);
	~MenuElement();
	sf::Vector2f GetPos();
	void SetNext(MenuElement* next);
	void SetPrev(MenuElement* prev);
	void ToggleDraw();
	void Select();
	MenuElement* Next();
	MenuElement* Previous();
	void Draw(sf::RenderWindow &w);
};
#endif