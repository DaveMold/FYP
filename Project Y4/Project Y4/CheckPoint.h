#ifndef _CHECKPOINT_H
#define _CHECKPOINT_H

//includes
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "Player.h"

class CheckPoint {
protected:
	//vairbles
	float DegreToRad_;
	sf::Text levelTimeText_;
	sf::Font font_;
	float numSides_;
	float width_, height_;
	sf::ConvexShape shape_;
	sf::Vector2f pos_;
	std::vector<sf::Vector2f> points_;
	Player::Shape playerShape_; //Stores the players shape for when they are needed to be respawned.
	sf::Vector2f playerPos_; //Stores the players posistion for when they are needed for spawning.
	bool collected_; //Will tell if the player has collected the checkpoint.
public:
	bool used_; //If the player has already been reset using the checkpoint they will not be reset and will be brought to the end game screen.
	CheckPoint(float Width, float Height, sf::Vector2f pos);
	~CheckPoint();
	void ResetPlayer(Player* p);
	void Draw(sf::RenderWindow &w);
	void SetPos(sf::RenderWindow &w);
	void Update(float time);
	void SetColor(sf::Color color);
	sf::Vector2f GetPos();
	sf::ConvexShape getShape();
	void collision(Player* p);
};
#endif
