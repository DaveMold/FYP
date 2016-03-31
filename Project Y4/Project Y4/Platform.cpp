#include "Platform.h"

Platform::Platform(float size, float sides, sf::Vector2f pos, Menu::ColorPresets preSet)
	:GameEntity(size, sides, pos, preSet){
	//Color Preset
	switch (preSet)
	{
	case Menu::ColorPresets::PRESETONE:
		shape.setOutlineColor(sf::Color::Green);
		break;
	case Menu::ColorPresets::PRESETTWO:
		shape.setOutlineColor(sf::Color(156, 37, 66)); //Ruby
		break;
	default:
		printf("Platform::Platform() ColorPresent not correct value.");
		break;
	}
	shape.setFillColor(sf::Color::Black);
}

Platform::Platform(float Width, float Height, float sides, sf::Vector2f pos, Menu::ColorPresets preSet)
	: GameEntity(Width, Height, sides, pos, preSet) {
	//Color Preset
	switch (preSet)
	{
	case Menu::ColorPresets::PRESETONE:
		shape.setOutlineColor(sf::Color::Green);
		break;
	case Menu::ColorPresets::PRESETTWO:
		shape.setOutlineColor(sf::Color(156, 37, 66)); //Ruby
		break;
	default:
		printf("Platform::Platform() ColorPresent not correct value.");
		break;
	}
	shape.setFillColor(sf::Color::Black);
}

Platform::~Platform() {

}
