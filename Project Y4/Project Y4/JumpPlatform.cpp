#include "JumpPlatform.h"

JumpPlatform::JumpPlatform(float size, float sides, sf::Vector2f pos)
	:GameEntity(size, sides, pos) {
	shape.setOutlineColor(sf::Color::Green);
	shape.setFillColor(sf::Color::Red);
}

JumpPlatform::JumpPlatform(float Width, float Height, float sides, sf::Vector2f pos)
	: GameEntity(Width, Height, sides, pos) {
	shape.setOutlineColor(sf::Color::Green);
	shape.setFillColor(sf::Color::Red);
}

JumpPlatform::~JumpPlatform() {

}