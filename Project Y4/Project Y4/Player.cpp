#include "Player.h"
#include "InputManager.h"

Player::Player(float size, float sides, sf::Vector2f pos)
	:GameEntity(size,sides,pos){
	shape.setOutlineColor(sf::Color::Blue);
	shape.setFillColor(sf::Color::Black);
	speed = 0;
	acceleration = 0.01;
	direction.x = (rand() % 10 - 5) / 60.0;
	direction.y = (rand() % 10 - 5) / 60.0;
}

void Player::Draw(sf::RenderWindow &w) {
	w.draw(shape);
}

void Player::SetPos(sf::RenderWindow &w) {

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
	}

	posCentre += (direction * speed) + g;
	rotation.rotate(rotateSpeed);

	for (int i = 0; i < shape.getPointCount(); i++) {
		points[i] = rotation * points[i];
	}
	for (int i = 0; i < shape.getPointCount(); i++) {
		shape.setPoint(i, points[i]);
	}
	shape.setPosition(posCentre);
}

sf::Vector2f Player::Vec2Multiply(sf::Vector2f v1, sf::Vector2f v2) {
	sf::Vector2f temp;
	temp.x = v1.x * v2.x;
	temp.y = v1.y * v2.y;
	return temp;
}