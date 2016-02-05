#include "Level.h"
#include "InputManager.h"

Level::Level(sf::RenderWindow &w): tileSize(25), platChar('1'), playerChar('2'), swapChar('3'), endLChar('4'), jumpPlatChar('5'){
	//player = new Player(25,4, sf::Vector2f(180,100));

	//swapPoints.push_back(new SwapPoint(25, sf::Vector2f(600, 350)));
	//platforms.push_back(new Platform(454, 54, 4, sf::Vector2f(125,400)));
	//platforms.push_back(new Platform(254, 54, 4, sf::Vector2f(400, 175)));

	//platforms.push_back(new Platform(25, 25, 4, sf::Vector2f(305, 450)));
	//platforms.push_back(new Platform(25, 25, 4, sf::Vector2f(250, 85)));
	//platforms.push_back(new Platform(25, 25, 4, sf::Vector2f(10, 10)));
	//platforms.push_back(new Platform(25, 25, 4, sf::Vector2f(20, 0)));
	//platforms.push_back(new Platform(25, 25, 4, sf::Vector2f(60, 680)));
	//platforms.push_back(new Platform(25, 25, 4, sf::Vector2f(305, 200)));

	//jumpPlatforms.push_back(new JumpPlatform(54, 24.5, 4, sf::Vector2f(315, 335)));

	//endGameGoal = new EndGameGoal(15, sf::Vector2f(550, 160), "SQUARE");
	//swapPoints.push_back(new SwapPoint(25, sf::Vector2f(600, 350)));
	//platforms.push_back(new Platform(454, 54, 4, sf::Vector2f(40,390)));
	/*platforms.push_back(new Platform(254, 54, 4, sf::Vector2f(400, 175)));
	jumpPlatforms.push_back(new JumpPlatform(54, 24.5, 4, sf::Vector2f(315, 335)));*/
	//platforms.push_back(new Platform(108, 54, 4, sf::Vector2f(325, 240)));
	//platforms.push_back(new Platform(108, 54, 4, sf::Vector2f(200, 320)));
	/*platforms.push_back(new Platform(54, 4, sf::Vector2f(450, 300)));
	platforms.push_back(new Platform(54, 4, sf::Vector2f(525, 300)));
	platforms.push_back(new Platform(54, 4, sf::Vector2f(600, 300)));
	platforms.push_back(new Platform(50, 3, sf::Vector2f(375, 225)));*/
}

void Level::LoadLevel(int fn) {
	int temp = 1 + fn;
	std::string tempString = "Assets/Levels/Level" + std::to_string(temp) + "Map.swg";
	//LevelMap file
	std::ifstream mapFile(tempString);
	std::vector<char> MapVals;//stores the maps values from file.

	if (mapFile.is_open())
	{
		while (!mapFile.eof())
		{
			//walk through file and grab each tile
			std::string str, value;
			std::getline(mapFile, str);
			std::stringstream stream(str);

			while (std::getline(stream, value, ' '))
			{
				if (value.length() > 0)
				{
					MapVals.push_back(value[0]);
				}
			}
			if (!MapVals.empty())
			{
				//update the map width
				width = MapVals.size() > width ? MapVals.size() : width;

				//Push back tiles
				m_map.push_back(MapVals);
				MapVals.clear();


			}
			//once we've finished loading, update the height
			height = m_map.size();
		}
	}
}

void Level::MapToLevel() {
	char temp;
	int lenght = 1;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < m_map.at(y).size(); x++) {

			temp = m_map.at(y).at(x);

			if (temp == platChar)
			{
				while (x+1 < m_map.at(y).size() && temp == m_map.at(y).at(x+1))
				{
					lenght++;
					x++;
				}

				platforms.push_back(new Platform(tileSize * lenght, tileSize, 4, sf::Vector2f((x * tileSize)-(tileSize * lenght), y* tileSize)));
				lenght = 1;
			}
			if (temp == jumpPlatChar)
			{
				while (x + 1 < m_map.at(y).size() && temp == m_map.at(y).at(x + 1))
				{
					lenght++;
					x++;
				}

				jumpPlatforms.push_back(new JumpPlatform(tileSize * lenght, tileSize, 4, sf::Vector2f((x * tileSize) - (tileSize * lenght), y* tileSize)));
				lenght = 1;
			}
			if (temp == playerChar)
			{
				player = new Player(tileSize, 4, sf::Vector2f(x * tileSize, y * tileSize));
			}
			if (temp == swapChar)
			{
				swapPoints.push_back(new SwapPoint(tileSize, sf::Vector2f(x * tileSize, y * tileSize)));
			}
			if (temp == endLChar)
			{
				endGameGoal = new EndGameGoal(15, sf::Vector2f(x * tileSize, y * tileSize), "SQUARE");
			}
		}
	}
}

Level::~Level() {
	player->~Player();
	endGameGoal->~EndGameGoal();
	for (int i = 0; i < swapPoints.size(); i++)
	{
		swapPoints[i]->~SwapPoint();
	}
	for (int i = 0; i < platforms.size(); i++)
	{
		platforms[i]->~Platform();
	}
	for (int i = 0; i < jumpPlatforms.size(); i++)
	{
		jumpPlatforms[i]->~JumpPlatform();
	}
}

bool Level::Update(sf::Vector2f g, sf::RenderWindow &w) {
	//look for the C Key in vector of keys pressed
	if (InputManager::instance()->Pressed("End"))
	{
		//change color of all objects
		player->SetColor(sf::Color::Red);
		for (auto itr = platforms.begin(); itr != platforms.end(); itr++)
		{
			(*itr)->SetColor(sf::Color::Blue);
		}
		for (auto itr = swapPoints.begin(); itr != swapPoints.end(); itr++)
		{
			(*itr)->SetColor(sf::Color::Green);
		}
	}

	//Platforms
	for (auto itr = platforms.begin(); itr != platforms.end(); itr++)
	{
		(*itr)->Update();

		std::pair<float, sf::Vector2f> temp;
		temp.first = false;
		if (player->SquareCircle(&(*itr)->getShape()))
		{
			temp = player->Collision(w, (*itr));
		}
		if (temp.first)
		{
			player->Update(g, temp.second);
		}
		else
		{
			player->Update(g, sf::Vector2f(0,0));
		}
	}
	//JumpPlatforms
	for (auto itr = jumpPlatforms.begin(); itr != jumpPlatforms.end(); itr++)
	{
		(*itr)->Update();
		std::pair<float, sf::Vector2f> temp = player->Collision(w, (*itr));
		if (temp.first)
		{
			player->ApplyJumpPlatformForce();
			player->Update(g, temp.second);
		}
		else
		{
			player->Update(g, sf::Vector2f(0, 0));
		}
	}
	//swapPoints
	SwapPointUpdate();
	//endGameGoal
	if (endGameGoal->collision(player))
	{
		AudioManager::instance()->PlayTrack("EndLevel");
		return true;
	}
	return false;
}

void Level::SwapPointUpdate() {
	std::vector<SwapPoint*>::iterator removeItr;
	bool remove = false;
	for (auto itr = swapPoints.begin(); itr != swapPoints.end(); itr++)
	{
		if ((*itr)->collision(player))
		{
			AudioManager::instance()->PlayTrack("SwapPoint");
			remove = true;
			removeItr = itr;
			player->ChangeActiveShape();
		}
	}
	if(remove)
		swapPoints.erase(removeItr);
}

sf::View Level::getFollowCamView() {
	return player->getView();
}

void Level::Draw(sf::RenderWindow &w) {

	for (auto itr = platforms.begin(); itr != platforms.end(); itr++)
	{
		(*itr)->Draw(w);
	}
	for (auto itr = jumpPlatforms.begin(); itr != jumpPlatforms.end(); itr++)
	{
		(*itr)->Draw(w);
	}
	for (auto itr = swapPoints.begin(); itr != swapPoints.end(); itr++)
	{
		(*itr)->Draw(w);
	}
	player->Draw(w);
	endGameGoal->Draw(w);
}
