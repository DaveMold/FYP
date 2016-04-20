#ifndef	_ONSCREENLABLE_H
#define _ONSCREENLABLE_H

//include
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <functional>
#include <iostream>

class OnScreenLable {
private:
	sf::Font font_; //Stores the font to load for the text to be rendered to the screen.
	bool draw_;//if false dont render.
public:
	sf::Text text_; //Store the text object to be rendered to the screen.
	OnScreenLable(sf::Vector2f pos, sf::String string, bool draw); //Creates the lable. setting the posiston to draw at, the value to display and weater or not it should be displayed.
	~OnScreenLable(); //Deconstructor.
	void SetText(sf::String s); //set the text of the lable.
	void SetPos(sf::Vector2f p); //sets the position the lable will render to.
	sf::Vector2f GetPos(); //returns the lables position.
	void ToggleDraw(); // toggles a bool to tell if the element should be rendered to the screen.
	void SetDraw(bool d); // sets the bool to tell if the element should be rendered to the screen.
	void Draw(sf::RenderWindow &w); //renders the lable if draw is set to true. else dose nothing.
};
#endif