#ifndef	LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Platform.h"
#include "JumpPlatform.h"
#include "SwapPoint.h"
#include "EndGameGoal.h"
#include "AudioManager.h"
#include "Menu.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Level {
private:
	Player* player_;
	std::vector<std::vector<char>> map_;
	int tileSize_, width_, height_;
	enum Shape { CIRCLE, SQUARE };
	std::vector<SwapPoint*> swapPoints_;
	std::vector<Platform*> platforms_;
	std::vector<JumpPlatform*> jumpPlatforms_;
	EndGameGoal* endGameGoal_;
	char platChar_, playerC_Char_, playerS_Char_, endLC_Char_, endLS_Char_, swapChar_, jumpPlatChar_;
	
public:
	Level(sf::RenderWindow &w);
	~Level();
	void LoadLevel(int fn);
	void MapToLevel(Menu::ColorPresets preSet);
	bool Update(sf::Vector2f g, sf::RenderWindow &w);
	void SwapPointUpdate(Player::Shape s);
	sf::View getFollowCamView();
	void Draw(sf::RenderWindow &w);
};
#endif