#include "Player.h"
#include "InputManager.h"

Player::Player(float size, float sides, sf::Vector2f pos)
	:GameEntity(size,sides,pos){
	shape.setOutlineColor(sf::Color::Blue);
	shape.setFillColor(sf::Color::Black);
	speed = 0;
	acceleration = 0.03;
	direction.x = 1;
	direction.y = 0;
	circle.setRadius(size);
	circle.setOutlineThickness(4);
	circle.setOutlineColor(sf::Color::Blue);
	circle.setFillColor(sf::Color::Black);
	type = shapeType::Square;
}

void Player::Draw(sf::RenderWindow &w) {
	switch (type)
	{
	case Player::Circle:
		w.draw(circle);
		break;
	default:
		w.draw(shape);
		break;
	}
}

void Player::SetPos(sf::Vector2f pos) {
	posCentre = pos;
}

#define FIND_KEY(key) std::find( begin, end, key ) != end //find a key in a vector	(tidies Update method)
void Player::Update(sf::Vector2f g) {
	speed = 0;

	std::vector<sf::String> const& keys = InputManager::instance()->getKeys();

	auto begin = keys.begin();
	auto end = keys.end();

	//look for the Left Arrow Key in vector of keys pressed
	if (FIND_KEY("Left"))
	{
		speed -= acceleration;
	}
	else if(FIND_KEY("Right")) 
	{
		speed += acceleration;
	}
	if (FIND_KEY("Up"))
	{
		std::cout << "Jump" << std::endl;
		SetPos(sf::Vector2f(400, 100));
	}
	if (FIND_KEY("PageUp"))
	{
		std::cout << "shapeType::Square" << std::endl;
		type = shapeType::Square;
	}
	if (FIND_KEY("PageDown"))
	{
		std::cout << "shapeType::Circle" << std::endl;
		type = shapeType::Circle;
	}

	posCentre += (direction * speed) + g;
	rotation.rotate(rotateSpeed);

	for (int i = 0; i < shape.getPointCount(); i++) {
		points[i] = rotation * points[i];
	}
	for (int i = 0; i < shape.getPointCount(); i++) {
		shape.setPoint(i, points[i]);
	}
	
	switch (type)
	{
	case Player::Circle:
		circle.setPosition(posCentre);
		break;
	default:
		shape.setPosition(posCentre);
		break;
	}
}

sf::Vector2f Player::Vec2Multiply(sf::Vector2f v1, sf::Vector2f v2) {
	sf::Vector2f temp;
	temp.x = v1.x * v2.x;
	temp.y = v1.y * v2.y;
	return temp;
}