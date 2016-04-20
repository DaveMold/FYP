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
	std::vector<std::vector<sf::Color>> map_; //stores all the valuse read from the file to use to populate the level.
	int tileSize_, width_, height_; //store the size of the level tiles.
	enum Shape { CIRCLE, SQUARE }; //Used to identify which shape is active.
	std::vector<DistructionObject*> distructionObjects_;//stores all the 
	std::vector<SwapPoint*> swapPoints_;//stores all the SwapPoints for the level.
	std::vector<Platform*> platforms_;//stores all the Platforms for the level.
	std::vector<CheckPoint*> checkPoints_;//stores all the CheckPoints for the level.
	std::vector<JumpPlatform*> jumpPlatforms_; //stores all the JumpPlatforms for the level.
	EndGameGoal* endGameGoal_; //Store the end level goal object for the level.
	//Colors are used to read the data from the images and populate the level map from the texture.
	//Colours (Reading)
	//empty color used to set a defualt empty value.
	const sf::Color EmptyRGB = sf::Color(0, 0, 0, 255);
	//Entities and their color values from reading from an image.
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
	Level(sf::RenderWindow &w); //creates an empty level with a time of zero.
	~Level(); //deconstructor.
	void clearLevel(); //clears all the entities form a level. for repopulation.
	float GetLevelTime(); //returns the level time.
	void ResetLevelTime(); //sets the level time back to zero incase a level is to be replaied.
	sf::Vector2f GetPlayerPos(); //returns the players posisiton in the level.
	void UpdateLevelTime(sf::Time totalTime); //updates the time the level has been on from the the time since game start and the time since the game started when we started in this current level.
	void MapToLevel(Menu::ColorPresets preSet); //loads the level data from the map and populates the level from its data.
	std::pair<bool, bool> Update(sf::Vector2f g, sf::RenderWindow &w, sf::Time runTime); /*Returns the out come of the level as two bools. The first signafies if the level is over. The
	secoud is wether or not the player passed the level. eg got to the end with the correct shape.*/
	void UpdateCheckPoints(); //checks what the colset checkpoint is for the background music to play form it. Also checks if the player has been killed or colected the chekpoint. then resets player if the checkpoint has been colected.
	void LoadLevelFromTexture(int fn); //loads the level data from the img to populate the map.
	void SwapPointUpdate(Player::Shape s); //plays the audio for swap points. also looks for the collision with the player to tell if the players shape should be changed.
	sf::View getFollowCamView(); //gets the follow camra sf::view from the player.
	void Draw(sf::RenderWindow &w); //renders the objects in the level.
};
#endif