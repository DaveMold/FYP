#include "Menu.h"


Menu::Menu(std::pair<float, float> windowDesmentions) : currentLevel(0), showSettings(false), preset(PRESETONE), gameOn(false), Exit(false), showExitConfermation(false), ShowLevelsSelect(false) {
	textures.reserve(12);
	for (int i = 0; i < textures.capacity(); i++)
	{
		textures.push_back(sf::Texture());
	}
	textures[0].loadFromFile("Assets/Menu/Yes.png");
	textures[1].loadFromFile("Assets/Menu/No.png");
	textures[2].loadFromFile("Assets/Menu/Start.png");
	textures[3].loadFromFile("Assets/Menu/Settings.png");
	textures[4].loadFromFile("Assets/Menu/Quit.png");
	textures[5].loadFromFile("Assets/Menu/Colors.png");
	textures[6].loadFromFile("Assets/Menu/Back.png");
	textures[7].loadFromFile("Assets/Menu/Preset1.png");
	textures[8].loadFromFile("Assets/Menu/Preset2.png");
	textures[9].loadFromFile("Assets/Menu/Levels.png");
	textures[10].loadFromFile("Assets/Menu/LevelOne.png");
	textures[11].loadFromFile("Assets/Menu/LevelTwo.png");


	//sprites.reserve(8);
	for (int i = 0; i < textures.size(); i++)
	{
		std::pair<sf::Sprite, bool> temp;
		temp.first = sf::Sprite();
		temp.second = false;
		sprites.push_back(temp);
		sprites[i].first.setTexture(textures[i]);
		if (i != 2)
			sprites[i].second = false;
		else
			sprites[i].second = true;
	}

	arrowHeadTexture.loadFromFile("Assets/Menu/ArrowHead.png");
	arrowHeadSprite.setTexture(arrowHeadTexture);

	//main menu
	/*Start*/sprites[2].first.setPosition(windowDesmentions.first/6, (windowDesmentions.second / 4.0f));
	/*Settings*/sprites[3].first.setPosition(windowDesmentions.first/6, sprites[2].first.getPosition().y + 50);
	/*Levels*/sprites[9].first.setPosition(windowDesmentions.first / 6, sprites[3].first.getPosition().y + 50);
	/*Exit*/sprites[4].first.setPosition(windowDesmentions.first/6, sprites[9].first.getPosition().y + 50);
	//settings menu
	sprites[5].first.setPosition((windowDesmentions.first / 4.0f) * 2.0f, windowDesmentions.second / 2.0f);
	sprites[7].first.setPosition(sprites[5].first.getPosition().x + sprites[6].first.getGlobalBounds().width, windowDesmentions.second / 2.0f);
	sprites[8].first.setPosition(sprites[5].first.getPosition().x + sprites[6].first.getGlobalBounds().width, windowDesmentions.second / 2.0f);
	sprites[6].first.setPosition(sprites[5].first.getPosition().x, windowDesmentions.second / 2.0f + 50);
	//exit confermation
	sprites[0].first.setPosition(sprites[4].first.getPosition().x - sprites[4].first.getLocalBounds().width / 2, sprites[4].first.getPosition().y + 50);
	sprites[1].first.setPosition(sprites[0].first.getPosition().x, sprites[0].first.getPosition().y + 50);
	//show level select
	sprites[10].first.setPosition(sprites[9].first.getPosition().x + 250, sprites[9].first.getPosition().y);
	sprites[11].first.setPosition(sprites[10].first.getPosition().x, sprites[10].first.getPosition().y + 50);
}

Menu::~Menu(){

}

#define FIND_KEY(key) std::find( begin, end, key ) != end //find a key in a vector	(tidies Update method)
#define FIND_KEY_LAST_UPDATE(key) std::find( begin_LU, end_LU, key ) != end_LU //find a key in a vector	(tidies Update method)
void Menu::Update() {

	/*std::vector<sf::String> const& keys = InputManager::instance()->getKeys();
	std::vector<sf::String> const& keys_LU = InputManager::instance()->getKeysLastUpdate();

	auto begin = keys.begin();
	auto end = keys.end();
	auto begin_LU = keys_LU.begin();
	auto end_LU = keys_LU.end();*/

	if (InputManager::instance()->Released("Up"))
	{
		AudioManager::instance()->PlayTrack("menuBoop");
			for (int i = 0; i < sprites.size(); i++)
			{
				if (sprites[i].second)
				{
					sprites[i].second = false;
					if (i < 2)
					{
						if (i == 0)
						{
							sprites[1].second = true;
							break;
						}
						else
						{
							sprites[0].second = true;
							break;
						}
					}
					else if (i > 1 && i < 5 || i == 9)
					{
						if (i == 2)
						{
							sprites[4].second = true;
							break;
						}
						else if (i == 3)
						{
							sprites[2].second = true;
							break;
						}
						else if (i == 9)
						{
							sprites[3].second = true;
							break;
						}
						else if (i == 4)
						{
							sprites[9].second = true;
							break;
						}
					}
					else if (i == 5 || i == 6)
					{
						if (i == 5)
						{
							sprites[6].second = true;
							break;
						}
						else if (i == 6)
						{
							sprites[5].second = true;
							break;
						}
					}
					else if (i == 10 || i == 11)
					{
						if (i == 10)
						{
							sprites[11].second = true;
							break;
						}
						else if (i == 11)
						{
							sprites[10].second = true;
							break;
						}
					}
				}
			}//end for
	}//end if FIND_KEY

	if (InputManager::instance()->Released("Down"))
	{
		AudioManager::instance()->PlayTrack("menuBoop");
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites[i].second)
			{
				sprites[i].second = false;
				if (i < 2)
				{
					if (i == 0)
					{
						sprites[1].second = true;
						break;
					}
					else
					{
						sprites[0].second = true;
						break;
					}
				}
				else if (i > 1 && i < 5 || i == 9)
				{
					if (i == 2)
					{
						sprites[3].second = true;
						break;
					}
					else if (i == 3)
					{
						sprites[9].second = true;
						break;
					}
					else if (i == 9)
					{
						sprites[4].second = true;
						break;
					}
					else if (i == 4)
					{
						sprites[2].second = true;
						break;
					}
				}
				else if (i == 5 || i == 6)
				{
					if (i == 5)
					{
						sprites[6].second = true;
						break;
					}
					else if (i == 6)
					{
						sprites[5].second = true;
						break;
					}
				}
				else if (i == 10 || i == 11)
				{
					if (i == 10)
					{
						sprites[11].second = true;
						break;
					}
					else if (i == 11)
					{
						sprites[10].second = true;
						break;
					}
				}
			}
		}//end for
	}//end if FIND_KEY

	if (InputManager::instance()->Released("Right"))
	{
		AudioManager::instance()->PlayTrack("Select");
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites[i].second)
			{
				if (i == 0)
				{
					Exit = true;
					break;
				}
				else if (i == 1)
				{
					showExitConfermation = false;
					sprites[i].second = false;
					sprites[2].second = true;
					break;
				}
				else if (i == 2)
				{
					gameOn = true;
					break;
				}
				else if (i == 3)
				{
					showSettings = true;
					sprites[i].second = false;
					sprites[5].second = true;
					break;
				}
				else if (i == 9)
				{
					ShowLevelsSelect = true;
					sprites[10].second = true;
					sprites[i].second = false;
					break;
				}
				else if (i == 4)
				{
					//Exit = true;
					showExitConfermation = true;
					sprites[0].second = true;
					sprites[4].second = false;
					break;
				}
				else if (i == 5)
				{
					if (preset == PRESETONE)
					{
						preset = PRESETTWO;
						break;
					}
					else if (preset == PRESETTWO)
					{
						preset = PRESETONE;
						break;
					}
				}
				else if (i == 6)
				{
					showSettings = false;
					sprites[i].second = false;
					sprites[2].second = true;
					break;
				}
				else if (i == 10)
				{
					currentLevel = 0;
					ShowLevelsSelect = false;
					sprites[i].second = false;
					sprites[9].second = true;
					break;
				}
				else if (i == 11)
				{
					currentLevel = 1;
					ShowLevelsSelect = false;
					sprites[i].second = false;
					sprites[9].second = true;
					break;
				}
			}
		}
	}
}

void Menu::Draw(sf::RenderWindow &w) {

	for (int i = 0; i < sprites.size(); i++)
	//This loop will set the posistion of the arrowHead to be pointing at the selected menu selection.
	{
		if (sprites[i].second)
			arrowHeadSprite.setPosition(sprites[i].first.getPosition().x /*- sprites[i].first.getGlobalBounds().width / 2.0f*/ - arrowHeadSprite.getGlobalBounds().width,
				sprites[i].first.getPosition().y);
	}

	w.draw(arrowHeadSprite);

	for (int i = 2; i < 5; i++)
	{
		w.draw(sprites[i].first);
		w.draw(sprites[9].first);
	}

	if (showExitConfermation)
	{
		w.draw(sprites[0].first);
		w.draw(sprites[1].first);
	}

	if (ShowLevelsSelect)
	{
		w.draw(sprites[10].first);
		w.draw(sprites[11].first);
	}

	if (showSettings)
	{
		w.draw(sprites[5].first);
		w.draw(sprites[6].first);
		switch (preset)
		{
		case PRESETONE:
			w.draw(sprites[7].first);
			break;
		case PRESETTWO:
			w.draw(sprites[8].first);
			break;
		}
	}
}