#include "SwapPoint.h"

SwapPoint::SwapPoint(float size, sf::Vector2f pos) :shapeSquare(numSides), collided(false) {
	activeShape = CIRCLE;
	shapeCircle.setRadius(size);
	posCentre = pos;
	radius = size;
	shapeCircle.setPosition(pos.x - radius, pos.y - radius);
	DegreToRad = 3.14 / 180;
	numSides = 4;
	posCentre = pos;
	points.reserve(numSides + 1);
	shapeSquare.setPosition(pos);
	shapeSquare.setPointCount(4);

	float indexOfPointsInCircle;

	for (int i = 0; i < numSides; i++) {
		indexOfPointsInCircle = /*degrees in circle / number of points*/ 360.0 / numSides;
		indexOfPointsInCircle = (i * indexOfPointsInCircle) + (indexOfPointsInCircle / 2);
		points.push_back(sf::Vector2f(cos(DegreToRad * indexOfPointsInCircle), sin(DegreToRad * indexOfPointsInCircle)));
	}
	width = sqrt(pow((points[2].x - points[1].x), 2) + pow((points[2].y - points[1].y), 2));
	height = width;

	for (int i = 0; i < numSides; i++) {
		points[i] *= radius;
	}
	for (int i = 0; i < numSides; i++) {
		shapeSquare.setPoint(i, points[i]);
	}


	shapeSquare.setOutlineThickness(-4);
	shapeSquare.setOutlineColor(sf::Color::Red);
	shapeSquare.setFillColor(sf::Color::Black);
	shapeCircle.setOutlineThickness(-4);
	shapeCircle.setOutlineColor(sf::Color::Red);
	shapeCircle.setFillColor(sf::Color::Black);
}

SwapPoint::~SwapPoint() {
}

void SwapPoint::Draw(sf::RenderWindow &w) {
	switch (activeShape)
	{
	case SQUARE:
		w.draw(shapeSquare);
		break;
	case CIRCLE:
		w.draw(shapeCircle);
		break;
	default:
		std::cout << "SwapPoint :: Draw Active Shape Default." << std::endl;
		break;
	}
}

void SwapPoint::SetPos(sf::RenderWindow &w) {
	posCentre = sf::Vector2f((rand() % (w.getSize().x - 2) + 5), (rand() % (w.getSize().y - 2) + 5));
}

void SwapPoint::SetColor(sf::Color color) {
	if (shapeSquare.getOutlineColor() != color)
		shapeSquare.setOutlineColor(color);
	if (shapeCircle.getOutlineColor() != color)
		shapeCircle.setOutlineColor(color);
}

void SwapPoint::ChangeActiveShape() {
	switch (activeShape)
	{
	case SQUARE:
		activeShape = CIRCLE;
		break;
	case CIRCLE:
		activeShape = SQUARE;
		break;
	default:
		std::cout << "change Active Shape Default." << std::endl;
		break;
	}
}

bool SwapPoint::collision(sf::Vector2f pos, float size) {
	if (sqrt(pow(posCentre.x - pos.x, 2) + pow(posCentre.y - pos.y, 2)) >
		radius + size && collided)
	{
		collided = false;
		ChangeActiveShape();
		return true;
	}
	else if (sqrt(pow(posCentre.x - pos.x, 2) + pow(posCentre.y - pos.y, 2)) <
		radius + size && collided == false)
	{
		collided = true;
		return false;
	}
	else
	{
		return false;
	}
}