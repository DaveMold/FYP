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

Player::~Player() {

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

void Player::SetPos(float x, float y) {
	posCentre = sf::Vector2f(x, y);
}

void Player::Update(sf::Vector2f g, sf::Vector2f collisionForce) {
	speed = 0;

	//look for the Left Arrow Key in vector of keys pressed
	if (InputManager::instance()->Held("Left"))
	{
		speed -= acceleration;
		//direction.x = direction.x * (-1);
		//direction.y = direction.y * (-1);
	}
	if(InputManager::instance()->Held("Right"))
	{
		speed += acceleration;
		//direction.x = direction.x * (1);
		//direction.y = direction.y * (1);
	}

	if (InputManager::instance()->Pressed("Up"))
	{
		switch (activeShape)
		{
		case CIRCLE:
			jumpForce = sf::Vector2f(0, -0.2502f);
			break;
		case SQUARE:
			jumpForce = sf::Vector2f(0, -0.2702f);
		}
	}
	else
	{
		if (jumpForce.y != 0.0f)
		{
			jumpForce = sf::Vector2f(0,jumpForce.y + 0.0001f);
		}
		if (jumpForce.y > 0.0f)
		{
			jumpForce.y == 0.0f;
		}
	}

	if (InputManager::instance()->Pressed("Home"))
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

sf::String Player::getShape() {
	switch (activeShape)
	{
	case SQUARE:
		return "SQUARE";
		break;
	case CIRCLE:
		return "CIRCLE";
		break;
	}
}