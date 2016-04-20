#ifndef	JUMPPLATFORM_H
#define JUMPPLATFORM_H
#include "GameEntity.h"


class JumpPlatform : public GameEntity {
private:

public:
	JumpPlatform(float size, float sides, sf::Vector2f pos, Menu::ColorPresets preSet); //Creates a jump platform by inheratin the GamesEntities base shape object. sets the new color present.
	JumpPlatform(float Width, float Height, float sides, sf::Vector2f pos, Menu::ColorPresets preSet); //Creates a jump platform by inheratin the GamesEntities base shape object but this time allowing for rectangles instead of just a square. sets the new color present.
	~JumpPlatform(); //deconstructor.
};
#endif