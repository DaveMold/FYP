#include "DistructionObject.h"

DistructionObject::DistructionObject(float size, float sides, sf::Vector2f pos, Menu::ColorPresets preSet)
	:GameEntity(size, sides , pos, preSet) {
	//Color Preset
	switch (preSet)
	{
	case Menu::ColorPresets::PRESETONE:
		shape.setOutlineColor(sf::Color::Red);
		break;
	case Menu::ColorPresets::PRESETTWO:
		shape.setOutlineColor(sf::Color(37, 156, 66)); //Ruby
		break;
	default:
		printf("DistructionObject::DistructionObject() ColorPresent not correct value.");
		break;
	}
	shape.setFillColor(sf::Color::Black);
}

DistructionObject::~DistructionObject() {

}
