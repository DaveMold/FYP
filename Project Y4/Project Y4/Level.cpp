#include "Level.h"
#include "InputManager.h"

Level::Level(sf::RenderWindow &w) {
	player = new Player(25,4, sf::Vector2f(180,100));
	swapPoints.push_back(new SwapPoint(25, sf::Vector2f(600, 350)));
	platforms.push_back(new Platform(454, 54, 4, sf::Vector2f(125,400)));
	platforms.push_back(new Platform(254, 54, 4, sf::Vector2f(400, 175)));
	jumpPlatforms.push_back(new JumpPlatform(54, 24.5, 4, sf::Vector2f(315, 335)));
	endGameGoal = new EndGameGoal(15, sf::Vector2f(550, 160), "SQUARE");
	//platforms.push_back(new Platform(108, 54, 4, sf::Vector2f(325, 240)));
	//platforms.push_back(new Platform(108, 54, 4, sf::Vector2f(200, 320)));
	/*platforms.push_back(new Platform(54, 4, sf::Vector2f(450, 300)));
	platforms.push_back(new Platform(54, 4, sf::Vector2f(525, 300)));
	platforms.push_back(new Platform(54, 4, sf::Vector2f(600, 300)));
	platforms.push_back(new Platform(50, 3, sf::Vector2f(375, 225)));*/
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
		std::pair<float, sf::Vector2f> temp = player->Collision(w, (*itr));
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
	for (auto itr = swapPoints.begin(); itr != swapPoints.end(); itr++)
	{
		if ((*itr)->collision(player->GetPos(), player->GetRadius()))
			player->ChangeActiveShape();
	}
	//endGameGoal
	if (endGameGoal->collision(player->GetPos(), player->GetRadius(), player->getShape()))
	{
		player->SetPos(180, 100);
		return true;
	}
	return false;
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
