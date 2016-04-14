#include "Level.h"
#include "InputManager.h"

Level::Level(sf::RenderWindow &w)
	: tileSize_(25), platChar_('1'), playerC_Char_('9'), checkPoint_Char_('2'), playerS_Char_('8'), swapChar_('3'), endLS_Char_('6'), endLC_Char_('7'), jumpPlatChar_('5')
{
	startLevelTime_ = startLevelTime_.Zero;
}

float Level::GetLevelTime() {
	return levelTime_.asSeconds();
}

sf::Vector2f Level::GetPlayerPos() {
	return player_->GetPos();
}

void Level::UpdateLevelTime(sf::Time totalTime) {
	//Record Level Time
	if (startLevelTime_ == startLevelTime_.Zero)
		startLevelTime_ = totalTime;
	levelTime_ = totalTime - startLevelTime_;
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

void Level::MapToLevel(Menu::ColorPresets preSet) {
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

				platforms_.push_back(new Platform(tileSize_ * lenght, tileSize_, 4, sf::Vector2f((x * tileSize_)-(tileSize_ * lenght), y* tileSize_), preSet));
				lenght = 1;
			}
			if (temp == jumpPlatChar_)
			{
				while (x + 1 < map_.at(y).size() && temp == map_.at(y).at(x + 1))
				{
					lenght++;
					x++;
				}

				jumpPlatforms_.push_back(new JumpPlatform(tileSize_ * lenght, tileSize_, 4, sf::Vector2f((x * tileSize_) - (tileSize_ * lenght), y* tileSize_), preSet));
				lenght = 1;
			}
			if (temp == checkPoint_Char_)
			{
				checkPoints_.push_back(new CheckPoint(tileSize_, tileSize_, sf::Vector2f((x * tileSize_), y * tileSize_)));
			}
			if (temp == playerC_Char_)
			{
				player_ = new Player(tileSize_, 4, sf::Vector2f(x * tileSize_, y * tileSize_), Player::CIRCLE, sf::Vector2f(width_ * tileSize_, height_ * tileSize_), preSet);
			}
			if (temp == playerS_Char_)
			{
				player_ = new Player(tileSize_, 4, sf::Vector2f(x * tileSize_, y * tileSize_), Player::SQUARE, sf::Vector2f(width_ * tileSize_, height_ * tileSize_), preSet);
			}
			if (temp == swapChar_)
			{
				swapPoints_.push_back(new SwapPoint(tileSize_, sf::Vector2f(x * tileSize_, y * tileSize_), preSet));
			}
			if (temp == endLS_Char_)
			{
				endGameGoal_ = new EndGameGoal(15, sf::Vector2f(x * tileSize_, y * tileSize_), "SQUARE", preSet);
			}
			if (temp == endLC_Char_)
			{
				endGameGoal_ = new EndGameGoal(15, sf::Vector2f(x * tileSize_, y * tileSize_), "CIRCLE", preSet);
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
	for (int i = 0; i < checkPoints_.size(); i++)
	{
		checkPoints_[i]->~CheckPoint();
	}
	map_.clear();
//	swapPoints_.clear();
//	platforms_.clear();
//	jumpPlatforms_.clear();
}

std::pair<bool,bool> Level::Update(sf::Vector2f g, sf::RenderWindow &w, sf::Time runTime) {
	//Record Level time.
	UpdateLevelTime(runTime);

	//Platforms
	for (auto itr = platforms_.begin(); itr != platforms_.end(); itr++)
	{
		(*itr)->Update();

		std::pair<float, sf::Vector2f> temp;
		temp.first = false;
		if (player_->SquareCircle(&(*itr)->getShape()))
		{
			temp = player_->CollisionWithPlayer(w, (*itr));
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
		std::pair<float, sf::Vector2f> temp = player_->CollisionWithPlayer(w, (*itr));
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
		AudioManager::instance()->PlayTrack("EndLevel", false);
		return std::make_pair<bool, bool>(true, true);
	}
	//CheckPoints
	UpdateCheckPoints();
	//Check player offscreen.
	if (player_->IsOffScreen())
	{
		for (auto R_itr = checkPoints_.rbegin(); R_itr != checkPoints_.rend(); R_itr++)
		{
			if (!(*R_itr)->used_ && (*R_itr)->collected_)
			{
				(*R_itr)->ResetPlayer(player_);
				return std::make_pair<bool, bool>(false, false);
			}
		}
		return std::make_pair<bool, bool>(true, false);
	}
	return std::make_pair<bool, bool>(false, true);
}

void Level::UpdateCheckPoints() {
	float min = FLT_MAX;
	std::vector<CheckPoint*>::iterator minItr;
	for (auto itrA = checkPoints_.begin(); itrA != checkPoints_.end(); itrA++)
	{
		float dis = (*itrA)->distanceTo(player_->GetPos());
		if (dis < min)
		{
			min = dis;
			minItr = itrA;
		}
		(*itrA)->Update(levelTime_.asSeconds());
		if ((*itrA)->collision(player_))
		{
			//If a checkPoint is collected the others are set back to active so they may be collected again.
			for (auto itrB = checkPoints_.begin(); itrB != checkPoints_.end(); itrB++)
			{
				if (itrB != itrA)
				{
					(*itrB)->ResetCheckPoint();
				}
			}
		}
	}
	AudioManager::instance()->SetSoundPos((*minItr)->GetPos(), "Background");
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
			AudioManager::instance()->PlayTrack("SwapPoint", false);
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
	//CheckPoints
	for (auto itr = checkPoints_.begin(); itr != checkPoints_.end(); itr++)
	{
		(*itr)->Draw(w);
	}
	player_->Draw(w);
	endGameGoal_->Draw(w);
}
