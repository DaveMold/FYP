#ifndef	LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Platform.h"
#include "JumpPlatform.h"
#include "SwapPoint.h"
#include "EndGameGoal.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Level {
private:
	Player* player;
	std::vector<std::vector<char>> m_map;
	int tileSize, width, height;
	enum Shape { CIRCLE, SQUARE };
	std::vector<SwapPoint*> swapPoints;
	std::vector<Platform*> platforms;
	std::vector<JumpPlatform*> jumpPlatforms;
	EndGameGoal* endGameGoal;
	char platChar, playerChar, endLChar, swapChar, jumpPlatChar;
	
public:
	Level(sf::RenderWindow &w);
	~Level();
	void LoadLevel(int fn);
	void MapToLevel();
	bool Update(sf::Vector2f g, sf::RenderWindow &w);
	void SwapPointUpdate();
	sf::View getFollowCamView();
	void Draw(sf::RenderWindow &w);

};
#endif