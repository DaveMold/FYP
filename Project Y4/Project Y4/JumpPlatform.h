#ifndef	JUMPPLATFORM_H
#define JUMPPLATFORM_H
#include "GameEntity.h"


class JumpPlatform : public GameEntity {
private:

public:
	JumpPlatform(float size, float sides, sf::Vector2f pos, Menu::ColorPresets preSet);
	JumpPlatform(float Width, float Height, float sides, sf::Vector2f pos, Menu::ColorPresets preSet);
	~JumpPlatform();
};
#endif