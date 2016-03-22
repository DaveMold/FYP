#pragma once
#ifndef	_ENDGAMEGOAL_H
#define _ENDGAMEGOAL_H

//includes
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <iostream>
#include "Player.h"

class EndGameGoal {
private:
	float DegreToRad;
	float radius;
	sf::CircleShape shapeCircle;
	sf::ConvexShape shapeSquare;
	sf::Vector2f posCentre;
	enum Shape { CIRCLE, SQUARE };
	Shape activeShape;
	float numSides;
	float width, height;
	std::vector<sf::Vector2f> points;
	bool collided;//If the player has collided with the swapPoint and is still overlaping with it.
public:
	EndGameGoal(float size, sf::Vector2f pos, sf::String active);
	~EndGameGoal();
	void ChangeActiveShape();
	void Draw(sf::RenderWindow &w);
	void SetPos(sf::RenderWindow &w);
	void SetColor(sf::Color color);
	bool collision(Player* p);
};
#endif