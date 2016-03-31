#ifndef PLAYER_H
#define PLAYER_H
#include "GameEntity.h"
#include "AudioManager.h"


class Player : public GameEntity {
public:
	enum Shape { CIRCLE, SQUARE };

	Player(float size, float sides, sf::Vector2f pos, Shape s, sf::Vector2f SBounds);
	~Player();
	void Draw(sf::RenderWindow &w);
	bool IsOffScreen(); //Returns true if the player has exited the screen bounds.
	void MoveUpdate();
	sf::View getView();
	void SetPos(float x, float y);
	void ApplyJumpPlatformForce();
	void ApplyJump(float collisionForce); /* This will check for the jump key press as well determin if the player should be aloud jump.
	It will then apply the correct magnatude of force for the shape. */
	void Update(sf::Vector2f g, sf::Vector2f collisionForce);
	sf::Vector2f Vec2Multiply(sf::Vector2f v1, sf::Vector2f v2);
	void ChangeActiveShape();
	Shape getShape();
	sf::ConvexShape getSquareShape();
	sf::CircleShape getCircleShape();
	sf::CircleShape getBoundingShape();
	bool SquareCircle(sf::Shape* s);
	float clamp(float value, const float min, const float max);

private:
	//debug
	bool debug;

	//vairbles
	sf::Vector2f screenBounds_; //Stores the bounds of the screen. If the player leaves the screen bounds they should be killed.
	sf::View followPlayer;
	sf::CircleShape shapeCircle, boundingCircle;
	float speed;
	float acceleration;
	sf::Vector2f resetPos;//Used to store the start posistion on this level.
	sf::Vector2f jumpForce;
	Shape activeShape;// will use enum Shape to check which shape is active.
	float radius;//stores the radius of the circle shape.
	float boundingOffSet;
};
#endif