#ifndef	LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Platform.h"
#include "SwapPoint.h"
#include "EndGameGoal.h"

class Level {
private:
	Player* player;
	enum Shape { CIRCLE, SQUARE };
	std::vector<SwapPoint*> swapPoints;
	std::vector<Platform*> platforms;
	EndGameGoal* endGameGoal;
public:
	Level(sf::RenderWindow &w);
	~Level();
	bool Update(sf::Vector2f g, sf::RenderWindow &w);
	void Draw(sf::RenderWindow &w);
};
#endif