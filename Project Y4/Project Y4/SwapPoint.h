#ifndef	_SWAPPOINT_H
#define _SWAPPOINT_H

//includes
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <iostream>
#include "Player.h"

class SwapPoint {
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
public:
	SwapPoint(float size, sf::Vector2f pos);
	~SwapPoint();
	void ChangeActiveShape();
	void Draw(sf::RenderWindow &w);
	void SetPos(sf::RenderWindow &w);
	void SetColor(sf::Color color);
	void setCollision(bool val);
	bool collision(Player* p);
};
#endif