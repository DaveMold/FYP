#include "Platform.h"

Platform::Platform(float size, float sides, sf::Vector2f pos)
	:GameEntity(size, sides, pos){
	shape.setOutlineColor(sf::Color::Green);
	shape.setFillColor(sf::Color::Black);
}

Platform::Platform(float Width, float Height, float sides, sf::Vector2f pos)
	: GameEntity(Width, Height, sides, pos) {
	shape.setOutlineColor(sf::Color::Green);
	shape.setFillColor(sf::Color::Black);
}

Platform::~Platform() {

}
