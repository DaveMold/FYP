#ifndef PLAYER_H
#define PLAYER_H
#include "GameEntity.h"


class Player : public GameEntity {

	//vairbles
	sf::CircleShape circle;
	sf::ConvexShape square;
	float speed;
	float acceleration;


public:
	Player(float size, float sides, sf::Vector2f pos);
	void Draw(sf::RenderWindow &w);
	void SetPos(sf::RenderWindow &w);
	void Update(sf::Vector2f g, sf::Vector2f collisionForce);
	sf::Vector2f Vec2Multiply(sf::Vector2f v1, sf::Vector2f v2);

};
#endif