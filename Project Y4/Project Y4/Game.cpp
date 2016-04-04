#pragma once
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "XInput9_1_0.lib")   // Library. If your compiler doesn't support this type of lib include change to the corresponding one

//Entities include
#include <iostream>
#include <fstream>
#include "json.h"
#include "Level.h"
#include "InputManager.h"
#include "Menu.h"
#include "OnScreenLable.h"

void SaveLevelData(int id, float time) {
	Json::Value levelDat;
	levelDat["ID"] = id;
	levelDat["Time"] = time;


	Json::StyledStreamWriter writer;

	std::ofstream test("Assets/Saves/Save1.sav");
	writer.write(test, levelDat);
}

std::pair<int, float> readLevelData() {
	std::pair<int, float> temp;
	Json::Value root;
	std::string line;
	Json::Reader reader;

	std::ifstream test("Assets/Saves/Save1.sav");

	if (reader.parse(test, root)) {
		temp.first = root["ID"].asInt();
		temp.second = root["Time"].asFloat();
	}
	else
	{
		printf("Could not find save file");
	}

	return temp;
}

int main()
{
	std::cout << readLevelData().second <<std::endl;
	std::cout << "Menu Controls \n Up/Down : Arrow Keys Up/Down. \n Sellect : Right Arrow Key" << std::endl;
	std::cout << "Game Controls \n Jump : Up Arrow Key. \n Movement : Right/Left Arrow Keys. \n Reset Pos = Home Key." << std::endl;
	std::cout << "GameOver Controls \n Back To Menu : Home Key." << std::endl;
	// Create the main window
	std::pair<float, float> windowDimentions;
	windowDimentions.first = 800;
	windowDimentions.second = 600;
	sf::RenderWindow window(sf::VideoMode(windowDimentions.first, windowDimentions.second, 32), "Project Y4");
	//step up end game scene
	sf::Texture GameOverTexture;
	sf::Sprite GameOverSprite;
	GameOverTexture.loadFromFile("Assets/Menu/GameOverScene.png");
	GameOverSprite.setTexture(GameOverTexture);
	GameOverSprite.setPosition(sf::Vector2f(0, 0));

	enum States { GAME, MENU, GAMEOVER };
	States GameState = MENU;
	//menu create
	Menu menu(windowDimentions);
	//set up fixed time.
	sf::Clock clock = sf::Clock();
	sf::Time elapsedTime;
	//Gravity
	sf::Vector2f gravity = sf::Vector2f(0, 0.0981);// 0.0981);
	//InputManager
	InputManager* inputMgr = InputManager::instance();
	//AudioManager
	AudioManager* audioMgr = AudioManager::instance();
	audioMgr->loadAudio();
	//Levels
	int levelCount = 3;
	int currentLevel = 0;
	std::vector<Level*> levels;
	for (int i = 0; i < levelCount; i++)
	{
		levels.push_back(new Level(window));
	}

	OnScreenLable levelTime(sf::Vector2f(windowDimentions.first - 500, 10), "Current Time : ", true );
	

	// Start game loop
	while (window.isOpen()) {
		// Process events
		sf::Event Event;

		while (window.pollEvent(Event)) {

			

			switch (Event.type) {
				// Close window : exit
			case sf::Event::Closed:
				for (std::vector<Level*>::iterator itr = levels.begin(); itr != levels.end(); itr++) {
					(*itr)->~Level();
				}
				menu.~Menu();
				window.close();
				break;
			case sf::Event::KeyPressed:
				inputMgr->KeyPressEvent(Event);
				break;
			case sf::Event::KeyReleased:
				inputMgr->KeyReleaseEvent(Event);
				break;
			default:
				break;
			}//end switch
		}//end while

		//Update

		if (menu.exit_)
		{
			window.close();
		}

		switch (GameState)
		{
		case GAME:
			if (levels[currentLevel]->Update(gravity, window, clock.getElapsedTime()))
			{
				SaveLevelData(currentLevel, levels[currentLevel]->GetLevelTime());
				menu.gameOn_ = false;
				GameState = GAMEOVER;
				levels[currentLevel]->~Level();
				break;
			}
			levelTime.SetPos(levels[currentLevel]->GetPlayerPos());
			levelTime.SetText("Current Time : \n" + std::to_string(levels[currentLevel]->GetLevelTime()));
			break;
		case GAMEOVER:
			if (inputMgr->Pressed("Home"))
			{
				GameState = MENU;
				menu.gameOn_ = false;
			}
			//std::cout << "State : GAMEOVER." << std::endl;
			break;
		case MENU:
			if (menu.gameOn_)
			{
				currentLevel = menu.currentLevel;
				levels[currentLevel]->LoadLevel(currentLevel);
				levels[currentLevel]->MapToLevel();
				GameState = GAME;
			}
			menu.Update();
			//std::cout << "State : MENU." << std::endl;
			break;
		}
		
		//prepare frame
		window.clear();
		
		switch (GameState)
		{
		case GAME:
			window.setView(levels[currentLevel]->getFollowCamView());
			levels[currentLevel]->Draw(window);
			levelTime.Draw(window);
			break;
		case GAMEOVER:
			window.setView(window.getDefaultView());
			window.draw(GameOverSprite);
			//std::cout << "State : GAMEOVER." << std::endl;
			break;
		case MENU:
			window.setView(window.getDefaultView());
			menu.Draw(window);
			//std::cout << "State : MENU." << std::endl;
			break;
		}

		// Finally, display rendered frame on screen
		window.display();
		//clock.restart();
	} //loop back for next frame

	return EXIT_SUCCESS;
}