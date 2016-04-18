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
#include "DistructionObject.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Level {
private:
	Player* player_;
	sf::Time startLevelTime_; //Stores the time the Curret Level was started at.
	sf::Time levelTime_; //Stores the time the player has been playing the current Level.
	std::vector<std::vector<sf::Color>> map_;
	int tileSize_, width_, height_;
	enum Shape { CIRCLE, SQUARE };
	std::vector<DistructionObject*> distructionObjects_;
	std::vector<SwapPoint*> swapPoints_;
	std::vector<Platform*> platforms_;
	std::vector<CheckPoint*> checkPoints_;
	std::vector<JumpPlatform*> jumpPlatforms_;
	EndGameGoal* endGameGoal_;
	//Colors are used to read the data from the images and populate the level map from the texture.
	//Colours (Reading)
	const sf::Color EmptyRGB = sf::Color(0, 0, 0, 0);
	//Entities
	const sf::Color DisObjRGB = sf::Color(255, 0, 0, 255);
	const sf::Color PlatRGB = sf::Color(0, 255, 33, 255);
	const sf::Color PlayerS_RGB = sf::Color(0, 0, 245, 255);
	const sf::Color PlayerC_RGB = sf::Color(0, 0, 255, 255);
	const sf::Color SwapRGB = sf::Color(255, 106, 0, 255);
	const sf::Color EndC_RGB = sf::Color(255, 245, 0, 255);
	const sf::Color EndS_RGB = sf::Color(245, 255, 0, 255);
	const sf::Color JPlatRGB = sf::Color(255, 0, 110, 255);
	const sf::Color CheckPointRGB = sf::Color(128, 128, 128, 255);
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
	void LoadLevelFromTexture(int fn);
	void SwapPointUpdate(Player::Shape s);
	sf::View getFollowCamView();
	void Draw(sf::RenderWindow &w);
};
#endif