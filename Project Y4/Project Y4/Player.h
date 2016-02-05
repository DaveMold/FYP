#ifndef PLAYER_H
#define PLAYER_H
#include "GameEntity.h"
#include "AudioManager.h"


class Player : public GameEntity {
	//debug
	bool debug;

	//vairbles
	sf::View followPlayer;
	sf::CircleShape shapeCircle, boundingCircle;
	float speed;
	float acceleration;
	sf::Vector2f resetPos;//Used to store the start posistion on this level.
	sf::Vector2f jumpForce;
	enum Shape { CIRCLE, SQUARE };
	Shape activeShape;// will use enum Shape to check which shape is active.
	float radius;//stores the radius of the circle shape.
	float boundingOffSet;
public:
	Player(float size, float sides, sf::Vector2f pos);
	~Player();
	void Draw(sf::RenderWindow &w);
	sf::View getView();
	void SetPos(float x, float y);
	void ApplyJumpPlatformForce();
	void Update(sf::Vector2f g, sf::Vector2f collisionForce);
	sf::Vector2f Vec2Multiply(sf::Vector2f v1, sf::Vector2f v2);
	void ChangeActiveShape();
	sf::String getShape();
	sf::ConvexShape getSquareShape();
	sf::CircleShape getCircleShape();
	sf::CircleShape getBoundingShape();
	bool SquareCircle(sf::Shape* s);
	float clamp(float value, const float min, const float max);
};
#endif