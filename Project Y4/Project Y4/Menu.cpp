#include "Menu.h"


Menu::Menu(std::pair<float, float> windowDesmentions) : currentLevel(0), showSettings_(false), preset_(PRESETONE), gameOn_(false), exit_(false), showExitConfermation_(false), ShowLevelsSelect_(false) {
	sf::String tempPath;
	sf::Vector2f tempPos;
	float itemOffSet = 50;

	arrowHeadTexture_.loadFromFile("Assets/Menu/ArrowHead.png");
	arrowHeadSprite_.setTexture(arrowHeadTexture_);

	//Main Menu
	tempPath = "Assets/Menu/Start.png";
	tempPos = sf::Vector2f(windowDesmentions.first / 6, windowDesmentions.second / 4.0f);
	elements_.push_back(new MenuElement(tempPos, tempPath, true, std::bind(&Menu::ToggleStartGame, this)));

	tempPath = "Assets/Menu/Settings.png";
	tempPos = sf::Vector2f(windowDesmentions.first / 6, elements_[0]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, tempPath, true, std::bind(&Menu::ToggleSettings, this)));

	tempPath = "Assets/Menu/Levels.png";
	tempPos = sf::Vector2f(windowDesmentions.first / 6, elements_[1]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, tempPath, true, std::bind(&Menu::ToggleLevelSelect, this)));

	tempPath = "Assets/Menu/Quit.png";
	tempPos = sf::Vector2f(windowDesmentions.first / 6, elements_[2]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, tempPath, true, std::bind(&Menu::ToggleExitConfermation, this)));
	
	elements_[0]->SetNext(elements_[3]);
	elements_[0]->SetPrev(elements_[1]);
	elements_[1]->SetNext(elements_[0]);
	elements_[1]->SetPrev(elements_[2]);
	elements_[2]->SetNext(elements_[1]);
	elements_[2]->SetPrev(elements_[3]);
	elements_[3]->SetNext(elements_[2]);
	elements_[3]->SetPrev(elements_[0]);

	//Settings
	tempPath = "Assets/Menu/Colors.png";
	tempPos = sf::Vector2f((windowDesmentions.first / 4.0f) * 2.0f, windowDesmentions.second / 2.0f);
	elements_.push_back(new MenuElement(tempPos, tempPath, false, std::bind(&Menu::ToggleColorPreset, this)));

	tempPath = "Assets/Menu/Back.png";
	tempPos = sf::Vector2f(elements_[4]->GetPos().x, elements_[4]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, tempPath, false, std::bind(&Menu::ResetSelect, this)));

	elements_[4]->SetNext(elements_[5]);
	elements_[4]->SetPrev(elements_[5]);
	elements_[5]->SetNext(elements_[4]);
	elements_[5]->SetPrev(elements_[4]);

	//Level Select
	tempPath = "Assets/Menu/LevelOne.png";
	tempPos = sf::Vector2f(elements_[2]->GetPos().x + itemOffSet*3, elements_[2]->GetPos().y);
	elements_.push_back(new MenuElement(tempPos, tempPath, false, std::bind(&Menu::ToggleColorPreset, this)));//**********************************************

	tempPath = "Assets/Menu/LevelTwo.png";
	tempPos = sf::Vector2f(elements_[6]->GetPos().x, elements_[6]->GetPos().y + itemOffSet);  
	elements_.push_back(new MenuElement(tempPos, tempPath, false, std::bind(&Menu::ToggleColorPreset, this)));//**********************************************

	elements_[6]->SetNext(elements_[7]);
	elements_[6]->SetPrev(elements_[7]);
	elements_[7]->SetNext(elements_[6]);
	elements_[7]->SetPrev(elements_[6]);

	//Y/N confermation
	tempPath = "Assets/Menu/Yes.png";
	tempPos = sf::Vector2f(elements_[3]->GetPos().x, elements_[3]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, tempPath, false, std::bind(&Menu::ToggleExit, this)));

	tempPath = "Assets/Menu/No.png";
	tempPos = sf::Vector2f(elements_[8]->GetPos().x + itemOffSet, elements_[8]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, tempPath, false, std::bind(&Menu::ResetSelect, this)));

	elements_[8]->SetNext(elements_[9]);
	elements_[8]->SetPrev(elements_[9]);
	elements_[9]->SetNext(elements_[8]);
	elements_[9]->SetPrev(elements_[8]);

	curretElement_ = elements_[0];
}

Menu::~Menu(){

}

void Menu::Update() {
	if (InputManager::instance()->Released("Up"))
	{
		AudioManager::instance()->PlayTrack("menuBoop");
		curretElement_ = curretElement_->Next();
	}

	if (InputManager::instance()->Released("Down"))
	{
		AudioManager::instance()->PlayTrack("menuBoop");
		curretElement_ = curretElement_->Previous();
	}

	if (InputManager::instance()->Released("Right"))
	{
		AudioManager::instance()->PlayTrack("Select");
		curretElement_->Select();
	}
}

void Menu::ToggleSettings() {
	curretElement_ = elements_[4];
	elements_[4]->ToggleDraw();
	elements_[5]->ToggleDraw();
}

void Menu::ToggleExitConfermation() {
	curretElement_ = elements_[8];
	elements_[8]->ToggleDraw();
	elements_[9]->ToggleDraw();
}

void Menu::ToggleLevelSelect() {
	curretElement_ = elements_[6];
	elements_[6]->ToggleDraw();
	elements_[7]->ToggleDraw();
}

void Menu::ToggleStartGame() {
	switch (gameOn_)
	{
	case true:
		gameOn_ = false;
		break;
	case false:
		gameOn_ = true;
		break;
	default:
		printf("Menu::ToggleStartGame - gameOn_ not valid.\n");
		break;
	}
}

void Menu::ToggleExit() {
	switch (exit_)
	{
	case true:
		exit_ = false;
		break;
	case false:
		exit_ = true;
		break;
	default:
		printf("Menu::ToggleExit - exit_ not valid.");
		break;
	}
}

void Menu::ToggleColorPreset() {
	curretElement_ = elements_[0];
	if (preset_ == PRESETONE)
	{
		preset_ = PRESETTWO;
	}
	else if (preset_ == PRESETTWO)
	{
		preset_ = PRESETONE;
	}
}

void Menu::ResetSelect() {
	curretElement_ = elements_[0];
	for (int i = 0; i < elements_.size(); i++)
	{
		if (i < 4)
			elements_[i]->SetDraw(true);
		else
			elements_[i]->SetDraw(false);
	}
}

void Menu::Draw(sf::RenderWindow &w) {
	arrowHeadSprite_.setPosition(curretElement_->GetPos().x /*- sprites[i].first.getGlobalBounds().width / 2.0f*/ - arrowHeadSprite_.getGlobalBounds().width,
		curretElement_->GetPos().y);
	w.draw(arrowHeadSprite_);

	for (int i = 0; i < elements_.size(); i++)
	{
		elements_[i]->Draw(w);
	}
}