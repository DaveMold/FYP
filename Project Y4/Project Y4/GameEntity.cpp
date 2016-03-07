#include "SFML/Graphics.hpp"
#include "GameEntity.h"


GameEntity::GameEntity(float size, float sides, sf::Vector2f pos):shape(sides) {
	rotateSpeed = 0;
	radius = size;
	numSides = sides;
	DegreToRad = 3.14 / 180;
	rotateSpeed = 0;
	posCentre = pos;
	points.reserve(numSides + 1);
	float indexOfPointsInCircle;

	/*shapes are created in the centre of a circle with radius "size",
	I devide the amount of sides by the degrees of a circle to get the
	intervals at which to posistion my points.*/
	switch (static_cast<int>(numSides))
	{
	case 3: //triangle
		/*as sf::shape will create with 0 degrees pointing left and not up,
		These figures are used to offset the triangle so it points up. */
		points.push_back(sf::Vector2f(cos(DegreToRad * 270), sin(DegreToRad * 270)));
		points.push_back(sf::Vector2f(cos(DegreToRad * 30), sin(DegreToRad * 30)));
		points.push_back(sf::Vector2f(cos(DegreToRad * 150), sin(DegreToRad * 150)));
		width = sqrt(pow((points[2].x - points[1].x), 2) + pow((points[2].y - points[1].y), 2));
		height = sqrt(pow(width,2) - (pow(width,2)/4.0f));
		break;
	default:
		for (int i = 0; i < numSides; i++) {
			indexOfPointsInCircle = /*degrees in circle / number of points*/ 360.0 / numSides;
			indexOfPointsInCircle = (i * indexOfPointsInCircle) + (indexOfPointsInCircle / 2);
			points.push_back(sf::Vector2f(cos(DegreToRad * indexOfPointsInCircle), sin(DegreToRad * indexOfPointsInCircle)));
		}
		width = sqrt(pow((points[2].x - points[1].x), 2) + pow((points[2].y - points[1].y), 2));
		height = width;
		break;
	}//end switch

	for (int i = 0; i < numSides; i++) {
		points[i] *= radius;
	}
	for (int i = 0; i < numSides; i++) {
		shape.setPoint(i, points[i]);
	}
	
	/*direction.x = (rand() % 10 - 5) / 60.0;
	direction.y = (rand() % 10 - 5) / 60.0;*/
	shape.setOutlineThickness(-4);
	shape.setOutlineColor(sf::Color::Green);
	shape.setFillColor(sf::Color::Black);
}

GameEntity::GameEntity(float Width, float Height, float sides, sf::Vector2f pos) :shape(sides) {
	rotateSpeed = 0;
	numSides = sides;
	DegreToRad = 3.14 / 180;
	rotateSpeed = 0;
	posCentre = pos;
	points.reserve(numSides + 1);
	width = Width;
	height = Height;

	//set points for a retangle or square.
	/*points.push_back(sf::Vector2f(posCentre.x - (Width / 2), posCentre.y - (Height / 2)));
	points.push_back(sf::Vector2f(posCentre.x + (Width / 2), posCentre.y - (Height / 2)));
	points.push_back(sf::Vector2f(posCentre.x - (Width / 2), posCentre.y + (Height / 2)));
	points.push_back(sf::Vector2f(posCentre.x + (Width / 2), posCentre.y + (Height / 2)));*/

	points.push_back(sf::Vector2f(0, 0));
	points.push_back(sf::Vector2f(width,0));
	points.push_back(sf::Vector2f(width, height));
	points.push_back(sf::Vector2f(0,height));

	for (int i = 0; i < numSides; i++) {
		shape.setPoint(i, points[i]);
	}

	/*direction.x = (rand() % 10 - 5) / 60.0;
	direction.y = (rand() % 10 - 5) / 60.0;*/
	shape.setOutlineThickness(-4);
	shape.setOutlineColor(sf::Color::Green);
	shape.setFillColor(sf::Color::Black);
}

void GameEntity::Draw(sf::RenderWindow &w) {
	w.draw(shape);
}

void GameEntity::SetPos(sf::RenderWindow &w) {
	posCentre = sf::Vector2f((rand() % (w.getSize().x - 2) + 5), (rand() % (w.getSize().y - 2) + 5));
}

void GameEntity::Update() {
	//posCentre += direction;
	rotation.rotate(rotateSpeed);

	for (int i = 0; i < shape.getPointCount(); i++) {
		points[i] = rotation * points[i];
	}
	for (int i = 0; i < shape.getPointCount(); i++) {
		shape.setPoint(i, points[i]);
	}
	shape.setPosition(posCentre);
}

void GameEntity::SetColor(sf::Color color) {
	if (shape.getOutlineColor() != color)
		shape.setOutlineColor(color);
	else
		shape.setOutlineColor(sf::Color::White);
}

sf::Vector2f GameEntity::GetPos() {
	return posCentre;
}

float GameEntity::GetRadius() {
	return radius;
}

sf::ConvexShape GameEntity::getShape() {
	return shape;
}

std::pair<bool, sf::Vector2f>  GameEntity::Collision(sf::RenderWindow &w, GameEntity* shape2) {
	float overLap = FLT_MAX;
	std::vector<sf::Vector2f> axisListShape1;
	std::vector<sf::Vector2f> axisListShape2;
	sf::Vector2f smallest;
	//axisListShape1 = GetAxis();
	//shape2->GetAxis(axisListShape1);
	sf::Vector2f projectionV1, projectionV2;
	float min, max, tempS1, tempS2;


	if (shape2->shape.getPosition().x + shape2->width/2.0f > this->shape.getPosition().x)
	{
		//Left
		axisListShape1 = GetAxis();
		shape2->GetAxis(axisListShape1);
	}
	else
	{
		//right
		axisListShape1 = GetAxis();
		shape2->GetAxis(axisListShape1);
		axisListShape1 = ReverseVector(axisListShape1);
	}

	//Project shapes onto axis
	//iterates through axisListShape1
	for (std::vector<sf::Vector2f>::iterator itr = axisListShape1.begin(); itr != axisListShape1.end(); itr++) {

		sf::Vector2f axis = *itr;

		projectionV1 = this->ProjectOnToAxis(axis);
		projectionV2 = shape2->ProjectOnToAxis(axis);

		std::pair<bool, float> result = checkOverlap(projectionV1, projectionV2);

		if (result.first) {
			// check for minimum
			if (result.second < overLap) {
				// then set this one as the smallest
				overLap = result.second;
				smallest = axis;

				sf::Vector2f d = posCentre - shape2->posCentre;
				if (vectorDotProduct(d, smallest) < 0)
					smallest = -smallest;
			}
		}
		else {
			return std::make_pair(false, sf::Vector2f());
		}
	}//end for

	/* MTV is the Minimum Translation Vector.
	 we multiply the smallest colliding axis (normalized) by the overlap to get
	 a vector that will separate the shapes with smallest magnitude.
	 smallest = vectorNormalize(smallest);*/

	 //if already moving away from each other
	if ((vectorDotProduct(this->GetDirection(), smallest) < 0)
		&&
		(vectorDotProduct(shape2->GetDirection(), smallest) < 0))
		return std::make_pair(true, sf::Vector2f(0, 0));

	//normalise smallest
	smallest = vectorNormalize(smallest);
	sf::Vector2f mtv = sf::Vector2f(smallest * (float)overLap);

	return std::make_pair(true, mtv);	//YES COLLISION

}//end Collision

 //Returns true if they overlap and the overlap distance if they do
std::pair<bool, double> GameEntity::checkOverlap(const sf::Vector2f &A, const sf::Vector2f &B) {

	if (A.x >= B.x && A.x <= B.y)
		return std::make_pair(true, B.y - A.x);
	else if (A.y >= B.x && A.y <= B.y)
		return std::make_pair(true, A.y - B.x);
	else
		return std::make_pair(false, 0);
}

sf::Vector2f GameEntity::ProjectOnToAxis(sf::Vector2f axis) const {
	//normalize the axis
	float magnitude = sqrt((axis.x * axis.x) + (axis.y * axis.y));
	//axis.x = axis.x / magnitude;
	axis /= magnitude;

	sf::Vector2f temp;

	temp.x = posCentre.x + this->width/2;
	temp.y = posCentre.y + this->height/2;

	//keep track of minimum and maximum points on the axis
	float min = vectorDotProduct(axis, this->shape.getPoint(0) + temp);
	float max = min;
	float p;

	//loop through the points and find the min and max values for projection
	for (int i = 1; i < points.size(); i++) {
		p = vectorDotProduct(axis, (this->shape.getPoint(i) + posCentre));
		if (p < min) {
			min = p;
		}
		else if (p > max) {
			max = p;
		}
	}

	sf::Vector2f proj = sf::Vector2f(min, max);
	return proj;
}

float GameEntity::vectorDotProduct(const sf::Vector2f &A, const sf::Vector2f &B) const{
	return (A.x * B.x) + (A.y * B.y);
}

sf::Vector2f GameEntity::GetDirection() {
	return direction;
}

std::vector<sf::Vector2f> GameEntity::GetAxis() {
	std::vector<sf::Vector2f> normalsList;
	sf::Vector2f normal;
	for (int PointOne = 0, PointTwo = 1; PointTwo < this->points.size(); PointOne++, PointTwo++) {
		/*normal.x = -(this->points[PointOne].y + this->points[PointTwo].y);
		normal.y = this->points[PointOne].x + this->points[PointTwo].x;*/

		sf::Vector2f pOne = this->points[PointOne];
		sf::Vector2f pTwo = this->points[PointTwo];

		sf::Vector2f temp = pOne - pTwo;

		normal.x = -temp.y;
		normal.y = temp.x;
		normalsList.push_back(normal);
	}
	return normalsList;
}

void GameEntity::GetAxis(std::vector<sf::Vector2f> normalsList) {
	sf::Vector2f normal;
	for (int PointOne = 0, PointTwo = 1; PointTwo < this->points.size(); PointOne++, PointTwo++) {

		sf::Vector2f pOne = this->points[PointOne];
		sf::Vector2f pTwo = this->points[PointTwo];

		sf::Vector2f temp = pOne - pTwo;

		normal.x = -temp.y;
		normal.y = temp.x;
		normalsList.push_back(normal);
	}
}

sf::Vector2f GameEntity::vectorNormalize(const sf::Vector2f &V) {
	float magnitude = sqrt((V.x * V.x) + (V.y * V.y));

	return V / magnitude;
}

std::vector<sf::Vector2f> GameEntity::ReverseVector(std::vector<sf::Vector2f> v) {
	std::vector<sf::Vector2f> vector;
	for (std::vector<sf::Vector2f>::reverse_iterator rev_itr = v.rbegin(); rev_itr != v.rend(); rev_itr++) {
		vector.push_back(*rev_itr);
	}
	return vector;
}
