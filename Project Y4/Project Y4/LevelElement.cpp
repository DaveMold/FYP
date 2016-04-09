#include "LevelElement.h"

LevelElement::LevelElement(sf::Vector2f pos, int levelID, sf::String string, bool draw, std::function<void(sf::String)> function)
	:MenuElement(pos, string, draw){
	funct_ = function;
	levelID_ = levelID;
	levelTimeText_.setFont(font_);
	levelTimeText_.setPosition(pos.x + 150,pos.y + 5);
	levelTimeText_.setString("Defualt");
	levelTimeText_.setColor(sf::Color(25,125,255.f));
	levelTimeText_.setCharacterSize(18);
	levelTimeText_.setStyle(sf::Text::Bold);
}

LevelElement::~LevelElement() {

}

void LevelElement::ReadLevelData() {
	Json::Value root;
	Json::Reader reader;

	std::ifstream buffer("Assets/Saves/Save1.sav");

	if (!reader.parse(buffer, root)) {
		std::cout << "Could not find save file" << std::endl;
		return;
	}
	Json::Value obj = root["Levels"];
	time_ = obj[levelID_].asFloat();
	
	buffer.close();
}

void LevelElement::UpdateLevelTime() {
	ReadLevelData();
	levelTimeText_.setString(" : " + std::to_string(time_));
}

void LevelElement::Draw(sf::RenderWindow &w) {
	if (draw_)
	{
		w.draw(text_);
		w.draw(levelTimeText_);
	}
}

void LevelElement::Select() {
	funct_(text_.getString());
}