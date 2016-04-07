#include "Player.h"
#include "InputManager.h"

Player::Player(float size, float sides, sf::Vector2f pos, Shape s)
	:GameEntity(size,sides,pos), debug(false), boundingOffSet(6){


	//Reset Posision.
	resetPos = pos;

	//Follow Camra Set-up
	followPlayer.setCenter(400, 300);
	followPlayer.setSize(800, 600);
	followPlayer.setViewport(sf::FloatRect(0, 0, 1, 1));

	activeShape = s;

	speed = 0;
	acceleration = 0.018;
	radius = size - 4;
	direction = sf::Vector2f(2, 0);
	jumpForce = sf::Vector2f(0, 0);

	//Bounding volume SetUp
	boundingCircle.setRadius(radius*boundingOffSet);
	boundingCircle.setPosition(pos.x - radius*boundingOffSet, pos.y - radius*boundingOffSet);
	boundingCircle.setOutlineThickness(-4);
	boundingCircle.setOutlineColor(sf::Color::Magenta);
	boundingCircle.setFillColor(sf::Color::Transparent);

	shapeCircle.setRadius(radius);
	shapeCircle.setPosition(pos.x - radius, pos.y - radius);

	shape.setOutlineColor(sf::Color::Blue);
	shape.setFillColor(sf::Color::Black);
	shape.setPosition(pos.x - radius, pos.y - radius);

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
	if (debug == true)
	{
		w.draw(boundingCircle);
	}
}

void Player::MoveUpdate() {

	speed = 0;

	//look for the Left Arrow Key in vector of keys pressed
	if ((InputManager::instance()->Pressed("Left") || InputManager::instance()->Held("Left")) && !InputManager::instance()->Released("Left"))
	{
		speed -= acceleration;
	}
	if ((InputManager::instance()->Pressed("Right") || InputManager::instance()->Held("Right")) && !InputManager::instance()->Released("Right"))

	{
		speed += acceleration;
	}
}

sf::View Player::getView() {
	return followPlayer;
}

void Player::SetPos(float x, float y) {
	posCentre = sf::Vector2f(x, y);
}

void Player::ApplyJumpPlatformForce() {
	AudioManager::instance()->PlayTrack("JumpPannel");
	switch (activeShape)
	{
	case SQUARE:
		jumpForce = sf::Vector2f(0, -0.3f);
		break;
	case CIRCLE:
		if (InputManager::instance()->Pressed("Left") || InputManager::instance()->Held("Left"))
		{
			jumpForce = sf::Vector2f(-0.1f, -0.2702f);
		}
		else
		{
			jumpForce = sf::Vector2f(0.1f, -0.2702f);
		}
		break;
	default:
		std::cout << "Player :: ApplyJumpPlatform Defualt." << std::endl;
		break;
	}
}

void Player::ApplyJump(sf::Vector2f collisionForce) {
	/*If the player is in contact with another object there will be a collsision force,
	so if the collsionion force is greater than 0, it must be colliding with somthing.*/
 	float collisionForceMagnatude = sqrt(pow(collisionForce.x, 2) + pow(collisionForce.y, 2));
	if (InputManager::instance()->Pressed("Up") && (collisionForceMagnatude != 0 && collisionForce.y < 0 && collisionForce.x != 0))
	{
		AudioManager::instance()->PlayTrack("Jump");
		switch (activeShape)
		{
		case CIRCLE:
			jumpForce = sf::Vector2f(jumpForce.x, -0.2502f);
			break;
		case SQUARE:
			jumpForce = sf::Vector2f(jumpForce.x, -0.2702f);
		}
	}
	else//if (InputManager::instance()->Released("Up"))
	{
		//y-axis reset
		if (jumpForce.y > 0.0f)
		{
			jumpForce.y = 0.0f;
		}
		if (jumpForce.y < 0.0f)
		{
			jumpForce = sf::Vector2f(jumpForce.x, jumpForce.y + 0.0001f);
		}
		//x-axis reset
		if (jumpForce.x > 0.0f)
		{
			jumpForce = sf::Vector2f(jumpForce.x - 0.0001f, jumpForce.y);
		}
		if (jumpForce.x < 0.0f)
		{
			jumpForce = sf::Vector2f(jumpForce.x + 0.0001f, jumpForce.y);
		}
	}
}



void Player::Update(sf::Vector2f g, sf::Vector2f collisionForce) {
	if (InputManager::instance()->Pressed("Delete"))
	{
		if (debug)
			debug = false;
		else
			debug = true;
	}
	if (InputManager::instance()->Pressed("Home"))
	{
		posCentre = resetPos;
	}

	MoveUpdate();

	
	ApplyJump(collisionForce);


	sf::Vector2f force = g + collisionForce + jumpForce;
	posCentre += force + (direction * speed);
	rotation.rotate(rotateSpeed);
	followPlayer.setCenter(posCentre.x, followPlayer.getCenter().y);
	boundingCircle.setPosition(posCentre.x - radius*boundingOffSet, posCentre.y - radius*boundingOffSet);

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

void Player::SetActiveShape(Shape s) {
	switch (s)
	{
	case SQUARE:
		activeShape = SQUARE;
		break;
	case CIRCLE:
		activeShape = CIRCLE;
		break;
	default:
		std::cout << "Player :: set Active Shape Default." << std::endl;
		break;
	}
}

Player::Shape Player::getShape() {
	return activeShape;
}

sf::ConvexShape Player::getSquareShape() {
	return shape;
}

sf::CircleShape Player::getCircleShape() {
	return shapeCircle;
}

sf::CircleShape Player::getBoundingShape() {
	return boundingCircle;
}

bool Player::SquareCircle(sf::Shape* s) {
	switch (activeShape)
	{
	case SQUARE:
		return shape.getGlobalBounds().intersects(s->getGlobalBounds());
		break;
	case CIRCLE:
		return shapeCircle.getGlobalBounds().intersects(s->getGlobalBounds());
		break;
	default:
		std::cout << "Player :: change Active Shape Default." << std::endl;
		return false;
		break;
	}
}

float Player::clamp(float value, const float min, const float max)
{
	value = std::min(value, max);
	value = std::max(value, min);

	return value;
}