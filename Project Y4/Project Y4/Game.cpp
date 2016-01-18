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
#include "Level.h"
#include "InputManager.h"
#include "Menu.h"

int main()
{
	// Create the main window
	enum States { GAME, MENU, GAMEOVER };
	States GameState = MENU;
	std::pair<float,float> windowDimentions;
	windowDimentions.first = 800;
	windowDimentions.second = 600;
	sf::RenderWindow window(sf::VideoMode(windowDimentions.first, windowDimentions.second, 32), "Project Y4");
	Menu menu(windowDimentions);
	sf::Clock clock = sf::Clock();
	sf::Time elapsedTime;
	Level level = Level(window);
	sf::Vector2f gravity = sf::Vector2f(0, 0.0981);// 0.0981);
	InputManager* inputMgr = InputManager::instance();

	// Start game loop
	while (window.isOpen()) {
		// Process events
		sf::Event Event;

		while (window.pollEvent(Event)) {



			switch (Event.type) {
				// Close window : exit
			case sf::Event::Closed:
				level.~Level();
				menu.~Menu();
				window.close();
				break;
			default:
				break;
			}//end switch
		}//end while

		//Update
		inputMgr->UpdatePressedKeys(Event);
		if (menu.Exit)
		{
			window.close();
		}
		if (menu.gameOn)
			GameState = GAME;

		switch (GameState)
		{
		case GAME:
			if (level.Update(gravity, window))
			{
				menu.gameOn = false;
				GameState = MENU;
				break;
			}
				//std::cout << "Game Over" << std::endl;
			break;
		case GAMEOVER:
			std::cout << "State : GAMEOVER." << std::endl;
			break;
		case MENU:
			menu.Update();
			std::cout << "State : MENU." << std::endl;
			break;
		}
		
		//prepare frame
		window.clear();

		switch (GameState)
		{
		case GAME:
			level.Draw(window);
			break;
		case GAMEOVER:
			std::cout << "State : GAMEOVER." << std::endl;
			break;
		case MENU:
			menu.Draw(window);
			std::cout << "State : MENU." << std::endl;
			break;
		}

		// Finally, display rendered frame on screen
		window.display();
		clock.restart();
	} //loop back for next frame

	return EXIT_SUCCESS;
}