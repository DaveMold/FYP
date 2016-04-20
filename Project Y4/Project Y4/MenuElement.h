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
	std::function< void() > funct_; //Stores a funtion pointer to run when the element has been selected.
public:
	sf::Text text_; //Stores the lable to be rendered to the screen.
	bool draw_;//if false dont render.
	sf::Font font_; //stores the font to display the text with.
	//Contructors for setting font size. the next and prerious element pointers and the store of the function pointer.
	MenuElement(sf::Vector2f pos, sf::String string, bool draw, MenuElement* next, MenuElement* previous, std::function<void()> function);
	MenuElement(sf::Vector2f pos, sf::String string, bool draw, std::function<void ()> function);
	MenuElement(sf::Vector2f pos, sf::String string, float f_size, bool draw, std::function<void()> function);
	MenuElement(sf::Vector2f pos, sf::String string, bool draw);
	~MenuElement(); //Deconstructor
	sf::Vector2f GetPos();//gets the postion of the menu element.
	void SetNext(MenuElement* next); //Sets the pointer to the nect element in the menu.
	void SetPrev(MenuElement* prev); //Sets the pointer to the previous element in the menu.
	void ToggleDraw(); // toggles a bool to tell if the element should be rendered to the screen.
	void SetDraw(bool d); // sets the bool to tell if the element should be rendered to the screen.
	virtual void Select(); //Runs the method stored in the function.
	MenuElement* Next(); //stores a pointer to the next menu element.
	MenuElement* Previous(); //stores a pointer to the previous munu element.
	virtual void Draw(sf::RenderWindow &w); //renders the text if draw is set to true.
};
#endif