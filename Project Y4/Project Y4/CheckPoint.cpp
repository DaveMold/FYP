#include "CheckPoint.h"

CheckPoint::CheckPoint(float Width, float Height, sf::Vector2f pos):shape_(14) {
	pos_ = sf::Vector2f(pos.x, pos.y - 8);
	numSides_ = 14;
	points_.reserve(numSides_ + 1);
	width_ = Width;
	height_ = Height;
	shape_.setPointCount(numSides_);
	shape_.setPosition(pos_);

	float indexW = width_ / 3.f;
	float indexH = height_ / 4.f;

	//set points of the shape.
	points_.push_back(sf::Vector2f(-(indexW * 5), indexH * 5));
	points_.push_back(sf::Vector2f(-(indexW * 4), indexH * 4));
	points_.push_back(sf::Vector2f(-(indexW * 4), -(indexH * 4)));
	points_.push_back(sf::Vector2f((indexW * 4), -(indexH * 4)));
	points_.push_back(sf::Vector2f(indexW * 4, (indexH * 4)));
	points_.push_back(sf::Vector2f((indexW * 5), indexH * 5));
	points_.push_back(sf::Vector2f((indexW), indexH * 5));
	points_.push_back(sf::Vector2f(indexW, (indexH * 4)));
	points_.push_back(sf::Vector2f((indexW * 3), (indexH * 4)));
	points_.push_back(sf::Vector2f(indexW * 3, -(indexH * 3)));
	points_.push_back(sf::Vector2f(-(indexW * 3), -(indexH * 3)));
	points_.push_back(sf::Vector2f(-(indexW * 3), (indexH * 4)));
	points_.push_back(sf::Vector2f(-(indexW), (indexH * 4)));
	points_.push_back(sf::Vector2f(-(indexW), (indexH * 5)));
	
	
	for (int i = 0; i < numSides_; i++) {
		shape_.setPoint(i, points_[i]);
	}
	shape_.setOutlineThickness(-2);
	shape_.setOutlineColor(sf::Color::Yellow);
	shape_.setFillColor(sf::Color::Black);


	//Level Time Display
	font_.loadFromFile("Assets/Menu/Squared Display.ttf");
	levelTimeText_.setFont(font_);
	levelTimeText_.setPosition(pos.x - (2.5f* indexW), pos.y - (2.5f * indexH));
	levelTimeText_.setString("00:00");
	levelTimeText_.setColor(sf::Color::Yellow);
	levelTimeText_.setCharacterSize(14);
	levelTimeText_.setStyle(sf::Text::Bold);
}

CheckPoint::~CheckPoint(){

}

void CheckPoint::ResetPlayer(Player* p) {
	if (collected_)
	{
		p->SetPos(playerPos_.x, playerPos_.y);
		p->SetActiveShape(playerShape_);
	}
}

void CheckPoint::Draw(sf::RenderWindow &w) {
	w.draw(shape_);
	w.draw(levelTimeText_);
}

void CheckPoint::SetPos(sf::RenderWindow &w) {

}

void CheckPoint::Update(float time) {
	for (int i = 0; i < shape_.getPointCount(); i++) {
		shape_.setPoint(i, points_[i]);
	}
	shape_.setPosition(pos_);

	if (!collected_)
	{
		//Update the Level time string and and trim the size.
		std::string timeS(std::to_string(time));
		timeS.resize(4);
		levelTimeText_.setString(timeS);
	}
}

void CheckPoint::SetColor(sf::Color color) {
	if (shape_.getOutlineColor() != color)
		shape_.setOutlineColor(color);
	else
		shape_.setOutlineColor(sf::Color::White);
}

sf::Vector2f CheckPoint::GetPos() {
	return pos_;
}

sf::ConvexShape CheckPoint::getShape(){
	return shape_;
}

void CheckPoint::collision(Player* p) {
	if (p->getShape() == Player::Shape::SQUARE)
	{
		if (shape_.getGlobalBounds().intersects(p->getSquareShape().getGlobalBounds()))
		{
			collected_ = true;
			playerPos_ = p->GetPos();
			playerShape_ = p->getShape();
		}
		else
		{
			return;
		}
	}
	else
	{
		if (shape_.getGlobalBounds().intersects(p->getCircleShape().getGlobalBounds()))
		{
			collected_ = true;
			playerPos_ = p->GetPos();
			playerShape_ = p->getShape();
		}
		else
		{
			return;
		}	
	}
}