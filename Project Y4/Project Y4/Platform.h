#ifndef	PLATFORM_H
#define PLATFORM_H
#include "GameEntity.h"


class Platform: public GameEntity{
private:

public:
	Platform(float size, float sides, sf::Vector2f pos, Menu::ColorPresets preSet); //Creates a platform by inheratin the GamesEntities base shape object. sets the new color present.
	Platform(float Width, float Height, float sides, sf::Vector2f pos, Menu::ColorPresets preSet); //Creates a platform by inheratin the GamesEntities base shape object but this time allowing for rectangles instead of just a square. sets the new color present.
	~Platform(); //Destructor.
};
#endif