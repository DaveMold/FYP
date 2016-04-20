#pragma once
#ifndef	_ENDGAMEGOAL_H
#define _ENDGAMEGOAL_H

//includes
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Menu.h"

class EndGameGoal {
private:
	float DegreToRad; //used to convert from degrees to radians.
	float radius; // stores the radius of the end game shapes.
	sf::CircleShape shapeCircle; //stores the circle shape for displaying the goal shape for the end of the level.
	sf::ConvexShape shapeSquare; //stores the square shape for the displaying the gaol of the end level goal, shape wise that is.
	sf::Vector2f posCentre; //stores the centre posistion of the two shapes.
	enum Shape { CIRCLE, SQUARE }; //used to determan witch shape is active.
	Shape activeShape; //stores the active shape.
	float numSides; //stores the number of sides for the square shape.
	float width, height; //stores the width and height the shape will take up on screen.
	std::vector<sf::Vector2f> points; //stores the points for the use of the shapes.
	bool collided;//If the player has collided with the swapPoint and is still overlaping with it.
public:
	EndGameGoal(float size, sf::Vector2f pos, sf::String active, Menu::ColorPresets preSet); //constructor that can take the pos, active shape and color preset.
	~EndGameGoal(); //deconstructor
	void ChangeActiveShape(); //change active shape to match the players shaps.
	void Draw(sf::RenderWindow &w); //Draws the endlevel goal shape depending in witch is active.
	void SetPos(sf::RenderWindow &w); //sets the posisiton of the endlevel goal.
	void SetColor(sf::Color color); // sets the outside color of the shapes.
	bool collision(Player* p); //basic collision detection wihich uses the distance between objects centre points and the radius of each object to return a bool for the result of the overlap.
};
#endif