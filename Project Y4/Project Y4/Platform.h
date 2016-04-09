#ifndef	PLATFORM_H
#define PLATFORM_H
#include "GameEntity.h"


class Platform: public GameEntity{
private:

public:
	Platform(float size, float sides, sf::Vector2f pos, Menu::ColorPresets preSet);
	Platform(float Width, float Height, float sides, sf::Vector2f pos, Menu::ColorPresets preSet);
	~Platform();
};
#endif