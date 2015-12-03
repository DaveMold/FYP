#include "Player.h"
#include "InputManager.h"

Player::Player(float size, float sides, sf::Vector2f pos)
	:GameEntity(size,sides,pos){

	activeShape = SQUARE;

	speed = 0;
	acceleration = 0.015;
	direction = sf::Vector2f(2, 0);
	jumpForce = sf::Vector2f(0, 0);

	radius = size-4;
	shapeCircle.setRadius(radius);
	shapeCircle.setPosition(pos.x - radius, pos.y - radius);

	shape.setOutlineColor(sf::Color::Blue);
	shape.setFillColor(sf::Color::Black);

	shapeCircle.setOutlineThickness(-4);
	shapeCircle.setOutlineColor(sf::Color::Blue);
	shapeCircle.setFillColor(sf::Color::Black);
}


void Player::Draw(sf::RenderWindow &w) {
	
	switch (activeShape)
	{
	case SQUARE:
		w.draw(shape);
		break;
	case CIRCLE:
		w.draw(shapeCircle);
		break;
	default:
		std::cout << "Player :: Draw Defualt." << std::endl;
		break;
	}
}

void Player::SetPos(sf::RenderWindow &w) {

}

#define FIND_KEY(key) std::find( begin, end, key ) != end //find a key in a vector	(tidies Update method)
#define REMOVE_KEY(key) std::remove( key ) //find a key in a vector	(tidies Update method)
void Player::Update(sf::Vector2f g, sf::Vector2f collisionForce) {
	speed = 0;

	std::vector<sf::String> const& keys = InputManager::instance()->getKeys();

	auto begin = keys.begin();
	auto end = keys.end();

	//look for the Left Arrow Key in vector of keys pressed
	if (FIND_KEY("Left"))
	{
		speed -= acceleration;
		//direction.x = direction.x * (-1);
		//direction.y = direction.y * (-1);
	}
	if(FIND_KEY("Right")) 
	{
		speed += acceleration;
		//direction.x = direction.x * (1);
		//direction.y = direction.y * (1);
	}

	if (FIND_KEY("Up"))
	{
		jumpForce = sf::Vector2f(0, -0.1502f);
		REMOVE_KEY("Up");
	}
	else
	{
		jumpForce = sf::Vector2f(0, 0);
	}


	/*if(!FIND_KEY("Up"))
	{
		jumpForce = sf::Vector2f(0, 0);
	}*/

	if (FIND_KEY("Home"))
	{
		posCentre = sf::Vector2f(100, 100);
	}

	//posCentre += (direction * speed) + g + collisionForce;
	sf::Vector2f force = g + collisionForce + jumpForce;
	posCentre += force + (direction * speed);
	rotation.rotate(rotateSpeed);

	switch (activeShape)
	{
	case SQUARE:
		for (int i = 0; i < shape.getPointCount(); i++) {
			points[i] = rotation * points[i];
		}
		for (int i = 0; i < shape.getPointCount(); i++) {
			shape.setPoint(i, points[i]);
		}
		shape.setPosition(posCentre);
		break;
	case CIRCLE:
		shapeCircle.setPosition(posCentre.x - radius, posCentre.y - radius);
		break;
	default:
		std::cout << "Player :: Update Defualt." << std::endl;
		break;
	}
}

sf::Vector2f Player::Vec2Multiply(sf::Vector2f v1, sf::Vector2f v2) {
	sf::Vector2f temp;
	temp.x = v1.x * v2.x;
	temp.y = v1.y * v2.y;
	return temp;
}

void Player::ChangeActiveShape() {
	switch (activeShape)
	{
	case SQUARE:
		activeShape = CIRCLE;
		break;
	case CIRCLE:
		activeShape = SQUARE;
		break;
	default:
		std::cout << "Player :: change Active Shape Default." << std::endl;
		break;
	}
}