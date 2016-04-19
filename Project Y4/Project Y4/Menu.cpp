#include "Menu.h"


Menu::Menu(std::pair<float, float> windowDesmentions) : currentLevel(0), showSettings_(false), preset_(PRESETONE), gameOn_(false), exit_(false), showExitConfermation_(false), ShowLevelsSelect_(false) {
	sf::String lable;
	sf::Vector2f tempPos;
	float itemOffSet = 50;

	arrowHeadTexture_.loadFromFile("Assets/Menu/ArrowHead.png");
	arrowHeadSprite_.setTexture(arrowHeadTexture_);

	//Main Menu
	lable = "Start";
	tempPos = sf::Vector2f(windowDesmentions.first / 6, windowDesmentions.second / 4.0f);
	elements_.push_back(new MenuElement(tempPos, lable, true, std::bind(&Menu::ToggleStartGame, this)));

	lable = "Settings";
	tempPos = sf::Vector2f(windowDesmentions.first / 6, elements_[0]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, lable, true, std::bind(&Menu::ToggleSettings, this)));

	lable = "Levels";
	tempPos = sf::Vector2f(windowDesmentions.first / 6, elements_[1]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, lable, true, std::bind(&Menu::ToggleLevelSelect, this)));

	lable = "Quit";
	tempPos = sf::Vector2f(windowDesmentions.first / 6, elements_[2]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, lable, true, std::bind(&Menu::ToggleExitConfermation, this)));
	
	elements_[0]->SetNext(elements_[3]);
	elements_[0]->SetPrev(elements_[1]);
	elements_[1]->SetNext(elements_[0]);
	elements_[1]->SetPrev(elements_[2]);
	elements_[2]->SetNext(elements_[1]);
	elements_[2]->SetPrev(elements_[3]);
	elements_[3]->SetNext(elements_[2]);
	elements_[3]->SetPrev(elements_[0]);

	//Settings
	lable = "Colors";
	tempPos = sf::Vector2f((windowDesmentions.first / 4.0f) * 2.0f, windowDesmentions.second / 4.0f);
	elements_.push_back(new MenuElement(tempPos, lable, false, std::bind(&Menu::ToggleColorPreset, this)));

	lable = "Preset1";
	tempPos = sf::Vector2f(elements_[4]->GetPos().x + (itemOffSet * 2), elements_[4]->GetPos().y);
	elements_.push_back(new MenuElement(tempPos, lable, false, std::bind(&Menu::ToggleColorPreset, this)));

	lable = "Preset2";
	tempPos = sf::Vector2f(elements_[4]->GetPos().x + (itemOffSet * 2), elements_[4]->GetPos().y);
	elements_.push_back(new MenuElement(tempPos, lable, false, std::bind(&Menu::ToggleColorPreset, this)));

	lable = "GAME\nLeft : go left\nRight : go right\nUp : jump\nHome : pause\nDelete : draw player bounding sphere\n\nMENU\nUp : next\nDown : previous\nRight : select\n\nENDGAME\nHome : return to menu\n\nPAUSE\nRight : return to game\nLeft : return to menu\n";
	tempPos = sf::Vector2f(elements_[4]->GetPos().x, elements_[4]->GetPos().y + (2.f * itemOffSet));
	elements_.push_back(new MenuElement(tempPos, lable, 0.5f, false, std::bind(&Menu::ResetSelect, this)));

	lable = "Back";
	tempPos = sf::Vector2f(elements_[4]->GetPos().x, elements_[4]->GetPos().y +(itemOffSet));
	elements_.push_back(new MenuElement(tempPos, lable, false, std::bind(&Menu::ResetSelect, this)));

	elements_[4]->SetNext(elements_[8]);
	elements_[4]->SetPrev(elements_[8]);
	elements_[8]->SetNext(elements_[4]);
	elements_[8]->SetPrev(elements_[4]);

	//Y/N confermation
	lable = "Yes";
	tempPos = sf::Vector2f(elements_[3]->GetPos().x, elements_[3]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, lable, false, std::bind(&Menu::ToggleExit, this)));

	lable = "No";
	tempPos = sf::Vector2f(elements_[9]->GetPos().x, elements_[9]->GetPos().y + itemOffSet);
	elements_.push_back(new MenuElement(tempPos, lable, false, std::bind(&Menu::ResetSelect, this)));

	elements_[9]->SetNext(elements_[10]);
	elements_[9]->SetPrev(elements_[10]);
	elements_[10]->SetNext(elements_[9]);
	elements_[10]->SetPrev(elements_[9]);

	//Level Select
	lable = "LevelOne";
	tempPos = sf::Vector2f(elements_[2]->GetPos().x + itemOffSet*3, elements_[2]->GetPos().y);
	elements_.push_back(new LevelElement(tempPos, 0, lable, false, std::bind(&Menu::SetLevel, this, lable)));

	lable = "LevelTwo";
	tempPos = sf::Vector2f(elements_[11]->GetPos().x, elements_[11]->GetPos().y + itemOffSet);  
	elements_.push_back(new LevelElement(tempPos, 1, lable, false, std::bind(&Menu::SetLevel, this, lable)));

	lable = "LevelThree";
	tempPos = sf::Vector2f(elements_[12]->GetPos().x, elements_[12]->GetPos().y + itemOffSet);
	elements_.push_back(new LevelElement(tempPos, 2, lable, false, std::bind(&Menu::SetLevel, this, lable)));

	lable = "LevelFour";
	tempPos = sf::Vector2f(elements_[13]->GetPos().x, elements_[13]->GetPos().y + itemOffSet);
	elements_.push_back(new LevelElement(tempPos, 3, lable, false, std::bind(&Menu::SetLevel, this, lable)));

	elements_[11]->SetNext(elements_[14]);
	elements_[11]->SetPrev(elements_[12]);
	elements_[12]->SetNext(elements_[11]);
	elements_[12]->SetPrev(elements_[13]);
	elements_[13]->SetNext(elements_[12]);
	elements_[13]->SetPrev(elements_[14]);
	elements_[14]->SetNext(elements_[13]);
	elements_[14]->SetPrev(elements_[11]);

	curretElement_ = elements_[0];
}

Menu::~Menu(){

}

void Menu::Update() {
	if (InputManager::instance()->Released("Up"))
	{
		AudioManager::instance()->PlayTrack("menuBoop", false);
		curretElement_ = curretElement_->Next();
	}

	if (InputManager::instance()->Released("Down"))
	{
		AudioManager::instance()->PlayTrack("menuBoop", false);
		curretElement_ = curretElement_->Previous();
	}

	if (InputManager::instance()->Released("Right"))
	{
		AudioManager::instance()->PlayTrack("Select", false);
		curretElement_->Select();
	}

	for (int i = 0; i < elements_.size(); i++)
	{
		auto temp = dynamic_cast<LevelElement*> (elements_[i]);
		if(temp != nullptr)
			temp->UpdateLevelTime();
	}
}

void Menu::ToggleSettings() {
	curretElement_ = elements_[4];
	elements_[4]->ToggleDraw();
	elements_[5]->ToggleDraw();
	elements_[7]->ToggleDraw();
	elements_[8]->ToggleDraw();
}

void Menu::ToggleExitConfermation() {
	curretElement_ = elements_[9];
	elements_[9]->ToggleDraw();
	elements_[10]->ToggleDraw();
}

void Menu::ToggleLevelSelect() {
	curretElement_ = elements_[11];
	elements_[11]->ToggleDraw();
	elements_[12]->ToggleDraw();
	elements_[13]->ToggleDraw();
	elements_[14]->ToggleDraw();
}

void Menu::SetLevel(sf::String s){
	ResetSelect();
	if (s == "LevelOne")
		currentLevel = 0;
	else if (s == "LevelTwo")
		currentLevel = 1;
	else if (s == "LevelThree")
		currentLevel = 2;
	else if (s == "LevelFour")
		currentLevel = 3;
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
	if (preset_ == PRESETONE)
	{
		elements_[5]->SetDraw(false);
		elements_[6]->SetDraw(true);
		preset_ = PRESETTWO;
	}
	else if (preset_ == PRESETTWO)
	{
		elements_[5]->SetDraw(true);
		elements_[6]->SetDraw(false);
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