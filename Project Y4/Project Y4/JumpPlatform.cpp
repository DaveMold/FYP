#include "JumpPlatform.h"

JumpPlatform::JumpPlatform(float size, float sides, sf::Vector2f pos, Menu::ColorPresets preSet)
	:GameEntity(size, sides, pos,preSet) {
	//Color Preset
	switch (preSet)
	{
	case Menu::ColorPresets::PRESETONE:
		shape.setOutlineColor(sf::Color::Green);
		break;
	case Menu::ColorPresets::PRESETTWO:
		shape.setOutlineColor(sf::Color(254,90,29)); //Orange
		break;
	default:
		printf("JumpPlatform::JumpPlatform() ColorPresent not correct value.");
		break;
	}
	shape.setFillColor(sf::Color::Red);
}

JumpPlatform::JumpPlatform(float Width, float Height, float sides, sf::Vector2f pos, Menu::ColorPresets preSet)
	: GameEntity(Width, Height, sides, pos, preSet) {
	//Color Preset
	switch (preSet)
	{
	case Menu::ColorPresets::PRESETONE:
		shape.setOutlineColor(sf::Color::Green);
		break;
	case Menu::ColorPresets::PRESETTWO:
		shape.setOutlineColor(sf::Color(254, 90, 29)); //Orange
		break;
	default:
		printf("JumpPlatform::JumpPlatform() ColorPresent not correct value.");
		break;
	}
	shape.setFillColor(sf::Color::Red);
}

JumpPlatform::~JumpPlatform() {

}