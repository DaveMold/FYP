#include "Level.h"
#include "InputManager.h"

Level::Level(sf::RenderWindow &w)
	: tileSize_(25)
{
	startLevelTime_ = startLevelTime_.Zero;
}

float Level::GetLevelTime() {
	return levelTime_.asSeconds();
}

void Level::ResetLevelTime() {
	levelTime_ = startLevelTime_.Zero;
	startLevelTime_ = levelTime_;
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

void Level::LoadLevelFromTexture(int fn) {
	sf::Image img;
	sf::Color color;
	sf::Vector2f imgDemtions;
	int temp = fn + 1;
	//If we can load image
	if (img.loadFromFile("Assets/Levels/Level" + std::to_string(temp) + "Map.png"))
	{

		//get image size
		imgDemtions.y = img.getSize().y;
		imgDemtions.x = img.getSize().x;

		//Loop Through the texture.
		for (int y = 0; y < imgDemtions.y; y++)
		{
			std::vector<sf::Color> mapX;
			for (int x = 0; x < imgDemtions.x; x++)
			{
				//get pixel.
				color = img.getPixel(x, y);
				if (color == sf::Color(255, 255, 255,0))
					color = sf::Color(0,0,0,255);
				//place each color into a vector for the X component.
				mapX.push_back(color);
			}//For end for cycling through x.
			//push the vector mapX into map_ Y vector.
			map_.push_back(mapX);
		}//For end for cycling through y.
		height_ = map_.size();
		//update the map width
		width_ = map_[0].size();
	}
	else
	{
		printf("No LevelTexture ezists for Level : " + temp);
	}
}

void Level::MapToLevel(Menu::ColorPresets preSet) {
	sf::Color temp;
	int lenght = 1;

	for (int y = 0; y < map_.size(); y++) {
		for (int x = 0; x < map_.at(y).size(); x++) {

			temp = map_.at(y).at(x);

			if (temp == PlatRGB)
			{
				while (x+1 < map_.at(y).size() && temp == map_.at(y).at(x+1))
				{
					lenght++;
					x++;
				}

				platforms_.push_back(new Platform(tileSize_ * lenght, tileSize_, 4, sf::Vector2f((x * tileSize_)-(tileSize_ * lenght), y* tileSize_), preSet));
				lenght = 1;
			}
			if (temp == DisObjRGB)
			{
				distructionObjects_.push_back(new DistructionObject(tileSize_, 6,sf::Vector2f((x * tileSize_), y * tileSize_), preSet));
			}
			if (temp == JPlatRGB)
			{
				while (x + 1 < map_.at(y).size() && temp == map_.at(y).at(x + 1))
				{
					lenght++;
					x++;
				}

				jumpPlatforms_.push_back(new JumpPlatform(tileSize_ * lenght, tileSize_, 4, sf::Vector2f((x * tileSize_) - (tileSize_ * lenght), y* tileSize_), preSet));
				lenght = 1;
			}
			if (temp == CheckPointRGB)
			{
				checkPoints_.push_back(new CheckPoint(tileSize_, tileSize_, sf::Vector2f((x * tileSize_), y * tileSize_)));
			}
			if (temp == PlayerC_RGB)
			{
				player_ = new Player(tileSize_, 4, sf::Vector2f(x * tileSize_, y * tileSize_), Player::CIRCLE, sf::Vector2f(width_ * tileSize_, height_ * tileSize_), preSet);
			}
			if (temp == PlayerS_RGB)
			{
				player_ = new Player(tileSize_, 4, sf::Vector2f(x * tileSize_, y * tileSize_), Player::SQUARE, sf::Vector2f(width_ * tileSize_, height_ * tileSize_), preSet);
			}
			if (temp == SwapRGB)
			{
				swapPoints_.push_back(new SwapPoint(tileSize_, sf::Vector2f(x * tileSize_, y * tileSize_), preSet));
			}
			if (temp == EndS_RGB)
			{
				endGameGoal_ = new EndGameGoal(15, sf::Vector2f(x * tileSize_, y * tileSize_), "SQUARE", preSet);
			}
			if (temp == EndC_RGB)
			{
				endGameGoal_ = new EndGameGoal(15, sf::Vector2f(x * tileSize_, y * tileSize_), "CIRCLE", preSet);
			}
		}
	}
}

Level::~Level() {
	
}

void Level::clearLevel() {
	delete player_;
	delete endGameGoal_;
	for (int i = 0; i < swapPoints_.size(); i++)
	{
		delete swapPoints_[i];
	}
	for (int i = 0; i < platforms_.size(); i++)
	{
		delete platforms_[i];
	}
	for (int i = 0; i < jumpPlatforms_.size(); i++)
	{
		delete jumpPlatforms_[i];
	}
	for (int i = 0; i < checkPoints_.size(); i++)
	{
		delete checkPoints_[i];
	}
	for (int i = 0; i < distructionObjects_.size(); i++)
	{
		delete distructionObjects_[i];
	}
	swapPoints_.clear();
	platforms_.clear();
	jumpPlatforms_.clear();
	checkPoints_.clear();
	distructionObjects_.clear();
	map_.clear();
}

std::pair<bool,bool> Level::Update(sf::Vector2f g, sf::RenderWindow &w, sf::Time runTime) {
	sf::Vector2f collisonF;
	//Record Level time.
	UpdateLevelTime(runTime);
	//Player
	player_->Update(g);
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
			collisonF += temp.second;
		}
		else
		{
			collisonF += sf::Vector2f(0,0);
		}
	}
	player_->UpdateCollisionForce(collisonF);
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
	//Distruction Objects
	for (auto itr = distructionObjects_.begin(); itr != distructionObjects_.end(); itr++)
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

			for (auto R_itr = checkPoints_.rbegin(); R_itr != checkPoints_.rend(); R_itr++)
			{
				if (!(*R_itr)->used_ && (*R_itr)->collected_)
				{
					(*R_itr)->ResetPlayer(player_);
					return std::make_pair<bool, bool>(false, false);
				}
			}
			AudioManager::instance()->PlayTrack("EndLevel", false);
			return std::make_pair<bool, bool>(true, false); 
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
	if(!checkPoints_.empty())
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
		AudioManager::instance()->PlayTrack("EndLevel", false);
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
	if (*minItr != NULL)
	{
		AudioManager::instance()->SetSoundPos((*minItr)->GetPos(), "Background");
	}
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
	for (auto itr = distructionObjects_.begin(); itr != distructionObjects_.end(); itr++)
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
