#ifndef	_SWAPPOINT_H
#define _SWAPPOINT_H

//includes
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Menu.h"

class SwapPoint {
private:
	float DegreToRad; //Used for degrees to Rad conversion.
	float radius; //Stores the radius of the shape.
	sf::CircleShape shapeCircle; //Stores the Circle shape for showing what shape the player will change to on contact.
	sf::ConvexShape shapeSquare; //Stores the Square shape for showing what shape the player will change to on contact.
	sf::Vector2f posCentre; //Stores the posistion of the shapes for drawing and collision.
	enum Shape { CIRCLE, SQUARE }; //Used to identify which shape is active.
	Shape activeShape; //Stores the active shape at the current moment.
	float numSides; //Stores the number of sides for the Square shape.
	float width, height; //Stores the width and height of the objects for collision checks.
	std::vector<sf::Vector2f> points; //Store the points needed to create the reevant Shape.
public:
	SwapPoint(float size, sf::Vector2f pos, Menu::ColorPresets preSet); //creates the shapes needed as well as setting their color preset.
	~SwapPoint(); //Deconstructor
	void ChangeActiveShape(Player::Shape s); //Changes the Swappoints active shape to be the opositte to the player. to show what they will become.
	Shape getShape(); //Returns access to the shapes for use out side the class.
	void Draw(sf::RenderWindow &w); //Renderes the active shape on the screen with the posistion set.
	void SetPos(sf::RenderWindow &w); //Update the posistion varible.
	void SetColor(sf::Color color); //Sets the out side of the shapes color.
	bool collision(Player* p); //Checks for basic collision with the player. Uses shape bounds and intersection to tell when there is a collision and returns a bool of the result.
};
#endif