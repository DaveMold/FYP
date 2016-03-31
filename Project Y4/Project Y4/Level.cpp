#include "Level.h"
#include "InputManager.h"

Level::Level(sf::RenderWindow &w)
	: tileSize_(25), platChar_('1'), playerC_Char_('9'), playerS_Char_('8'), swapChar_('3'), endLS_Char_('6'), endLC_Char_('7'), jumpPlatChar_('5')
{
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
				width_ = MapVals.size() > width_ ? MapVals.size() : width_;

				//Push back tiles
				map_.push_back(MapVals);
				MapVals.clear();


			}
			//once we've finished loading, update the height
			height_ = map_.size();
		}
	}
}

void Level::MapToLevel() {
	char temp;
	int lenght = 1;

	for (int y = 0; y < height_; y++) {
		for (int x = 0; x < map_.at(y).size(); x++) {

			temp = map_.at(y).at(x);

			if (temp == platChar_)
			{
				while (x+1 < map_.at(y).size() && temp == map_.at(y).at(x+1))
				{
					lenght++;
					x++;
				}

				platforms_.push_back(new Platform(tileSize_ * lenght, tileSize_, 4, sf::Vector2f((x * tileSize_)-(tileSize_ * lenght), y* tileSize_)));
				lenght = 1;
			}
			if (temp == jumpPlatChar_)
			{
				while (x + 1 < map_.at(y).size() && temp == map_.at(y).at(x + 1))
				{
					lenght++;
					x++;
				}

				jumpPlatforms_.push_back(new JumpPlatform(tileSize_ * lenght, tileSize_, 4, sf::Vector2f((x * tileSize_) - (tileSize_ * lenght), y* tileSize_)));
				lenght = 1;
			}
			if (temp == playerC_Char_)
			{
				player_ = new Player(tileSize_, 4, sf::Vector2f(x * tileSize_, y * tileSize_), Player::CIRCLE, sf::Vector2f(width_ * tileSize_, height_ * tileSize_));
			}
			if (temp == playerS_Char_)
			{
				player_ = new Player(tileSize_, 4, sf::Vector2f(x * tileSize_, y * tileSize_), Player::SQUARE, sf::Vector2f(width_ * tileSize_, height_ * tileSize_));
			}
			if (temp == swapChar_)
			{
				swapPoints_.push_back(new SwapPoint(tileSize_, sf::Vector2f(x * tileSize_, y * tileSize_)));
			}
			if (temp == endLS_Char_)
			{
				endGameGoal_ = new EndGameGoal(15, sf::Vector2f(x * tileSize_, y * tileSize_), "SQUARE");
			}
			if (temp == endLC_Char_)
			{
				endGameGoal_ = new EndGameGoal(15, sf::Vector2f(x * tileSize_, y * tileSize_), "CIRCLE");
			}
		}
	}
}

Level::~Level() {
	player_->~Player();
	endGameGoal_->~EndGameGoal();
	for (int i = 0; i < swapPoints_.size(); i++)
	{
		swapPoints_[i]->~SwapPoint();
	}
	for (int i = 0; i < platforms_.size(); i++)
	{
		platforms_[i]->~Platform();
	}
	for (int i = 0; i < jumpPlatforms_.size(); i++)
	{
		jumpPlatforms_[i]->~JumpPlatform();
	}
}

bool Level::Update(sf::Vector2f g, sf::RenderWindow &w) {
	if (player_->IsOffScreen())
	{
		return true;
	}

	//Platforms
	for (auto itr = platforms_.begin(); itr != platforms_.end(); itr++)
	{
		(*itr)->Update();

		std::pair<float, sf::Vector2f> temp;
		temp.first = false;
		if (player_->SquareCircle(&(*itr)->getShape()))
		{
			temp = player_->Collision(w, (*itr));
		}
		if (temp.first)
		{
			player_->Update(g, temp.second);
		}
		else
		{
			player_->Update(g, sf::Vector2f(0,0));
		}
	}
	//JumpPlatforms
	for (auto itr = jumpPlatforms_.begin(); itr != jumpPlatforms_.end(); itr++)
	{
		(*itr)->Update();
		std::pair<float, sf::Vector2f> temp = player_->Collision(w, (*itr));
		if (temp.first)
		{
			player_->ApplyJumpPlatformForce();
		}
	}
	//swapPoints
	SwapPointUpdate(player_->getShape());
	//endGameGoal
	if (endGameGoal_->collision(player_))
	{
		AudioManager::instance()->PlayTrack("EndLevel");
		return true;
	}
	return false;
}

void Level::SwapPointUpdate(Player::Shape s) {
	std::vector<SwapPoint*>::iterator removeItr;
	bool remove = false;
	for (auto itr = swapPoints_.begin(); itr != swapPoints_.end(); itr++)
	{
		if (player_->getShape() == (*itr)->getShape())
			(*itr)->ChangeActiveShape(player_->getShape());
		if ((*itr)->collision(player_))
		{
			AudioManager::instance()->PlayTrack("SwapPoint");
			remove = true;
			removeItr = itr;
			player_->ChangeActiveShape();
		}
	}
	if(remove)
		swapPoints_.erase(removeItr);
}

sf::View Level::getFollowCamView() {
	return player_->getView();
}

void Level::Draw(sf::RenderWindow &w) {
	for (auto itr = platforms_.begin(); itr != platforms_.end(); itr++)
	{
		(*itr)->Draw(w);
	}
	for (auto itr = jumpPlatforms_.begin(); itr != jumpPlatforms_.end(); itr++)
	{
		(*itr)->Draw(w);
	}
	for (auto itr = swapPoints_.begin(); itr != swapPoints_.end(); itr++)
	{
		(*itr)->Draw(w);
	}
	player_->Draw(w);
	endGameGoal_->Draw(w);
}
