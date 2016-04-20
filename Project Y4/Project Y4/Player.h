#ifndef PLAYER_H
#define PLAYER_H
#include "GameEntity.h"
#include "AudioManager.h"


class Player : public GameEntity {
public:
	enum Shape { CIRCLE, SQUARE }; //Used to identify which shape is active.

	Player(float size, float sides, sf::Vector2f pos, Shape s, sf::Vector2f SBounds, Menu::ColorPresets preSet); //Creates the circle shape as well as calls the constrtor for a gameEntity to create the square. It will also set the color preset and screen bounds.
	~Player(); //Deconstructor
	void Draw(sf::RenderWindow &w); //Renders the active shape to the screen useing the posistion provided.
	void UpdateCollisionForce(sf::Vector2f collisionForce); //when an object collisdes with a player they should update the players collision force.
	bool IsOffScreen(); //Returns true if the player has exited the screen bounds.
	void MoveUpdate(); //Performs the code to check for a key down using the input manager. It then will apply the aproprate acceleration. This is used to keep the Player::Update() cleaner.
	sf::View getView(); //Get the sf::view witch follows the player for the update of the camra posistion.
	void SetPos(float x, float y); //Sets the player posistion.
	sf::Vector2f GetPos(); //gets the player posistion
	void ApplyJumpPlatformForce(); //this will use the inputManager to determan what direction to player was moveing. it then apply a force to the shape depending of if it is a circle or square(square jump heigh, Circle move faster).
	void ApplyJump(sf::Vector2f collisionForce); /* This will check for the jump key press as well determin if the player should be aloud jump.
	It will then apply the correct magnatude of force for the shape. */
	void Update(sf::Vector2f g); //checks if the collisions bounding sphere should be drawn(debug option). acumulates all the forces acting on the player and creates one force from them to be applied to the players shapes.
	sf::Vector2f Vec2Multiply(sf::Vector2f v1, sf::Vector2f v2); //Multiplacation for Vector 2's.
	void ChangeActiveShape(); //swaps the active shape for the player.
	Shape getShape(); //returns the players shape.
	sf::ConvexShape getSquareShape(); //return  the square shape.
	sf::CircleShape getCircleShape(); //returns the circle shape.
	sf::CircleShape getBoundingShape(); //returns the bounding sheres shape.
	bool SquareCircle(sf::Shape* s); //collsision detection for a square and a circle. using distance between centres and radius of objects.
	float clamp(float value, const float min, const float max); //Clamps a value to witin a range.
	void SetActiveShape(Shape s); //Sets the players active shape.
private:
	//debug
	bool debug; //toggles the draw of the bounding sphere.

	//vairbles
	sf::Vector2f collisionForce_; //Stores the collision force being applied to the player.
	sf::Vector2f screenBounds_; //Stores the bounds of the screen. If the player leaves the screen bounds they should be killed.
	sf::View followPlayer; //store a view that is focused on following the players movments
	sf::CircleShape shapeCircle, boundingCircle; //Stores the two circle shapes for the player.
	float speed; //The value the player will move by.
	const float maxSpeed_ = 10.75f; //The max speed the player can obtain.
	float accelerationS_, accelerationC_; //The acceleration that is applied to the speed when the player is attempting to move.
	sf::Vector2f resetPos;//Used to store the start posistion on this level.
	sf::Vector2f jumpForce; //The jump force is used to conter the effects of gravity when the player press Up.
	Shape activeShape;// will use enum Shape to check which shape is active.
	float radius;//stores the radius of the circle shape.
	float boundingOffSet; //Used to offset the bounding sphere to the correct positon for the player.
};
#endif