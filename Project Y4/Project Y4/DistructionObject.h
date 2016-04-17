#ifndef	DISTRUCTIONOBJECT_H
#define DISTRUCTIONOBJECT_H
#include "GameEntity.h"


class DistructionObject : public GameEntity {
private:

public:
	DistructionObject(float size, float sides, sf::Vector2f pos, Menu::ColorPresets preSet);
	~DistructionObject();
};
#endif