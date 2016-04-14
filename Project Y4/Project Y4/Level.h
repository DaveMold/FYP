#ifndef	LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Platform.h"
#include "JumpPlatform.h"
#include "SwapPoint.h"
#include "EndGameGoal.h"
#include "AudioManager.h"
#include "CheckPoint.h"
#include "Menu.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Level {
private:
	Player* player_;
	sf::Time startLevelTime_; //Stores the time the Curret Level was started at.
	sf::Time levelTime_; //Stores the time the player has been playing the current Level.
	std::vector<std::vector<char>> map_;
	int tileSize_, width_, height_;
	enum Shape { CIRCLE, SQUARE };
	std::vector<SwapPoint*> swapPoints_;
	std::vector<Platform*> platforms_;
	std::vector<CheckPoint*> checkPoints_;
	std::vector<JumpPlatform*> jumpPlatforms_;
	EndGameGoal* endGameGoal_;
	char platChar_, playerC_Char_, playerS_Char_, checkPoint_Char_, endLC_Char_, endLS_Char_, swapChar_, jumpPlatChar_;
	
public:
	Level(sf::RenderWindow &w);
	~Level();
	float GetLevelTime();
	sf::Vector2f GetPlayerPos();
	void UpdateLevelTime(sf::Time totalTime);
	void MapToLevel(Menu::ColorPresets preSet);
	std::pair<bool, bool> Update(sf::Vector2f g, sf::RenderWindow &w, sf::Time runTime); /*Returns the out come of the level as two bools. The first signafies if the level is over. The
	secoud is wether or not the player passed the level. eg got to the end with the correct shape.*/
	void UpdateCheckPoints();
	void LoadLevel(int fn);
	void SwapPointUpdate(Player::Shape s);
	sf::View getFollowCamView();
	void Draw(sf::RenderWindow &w);
};
#endif