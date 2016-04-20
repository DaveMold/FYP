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
	sf::Text levelTimeText_; //stores the text to be rendered to the screen inside the checkpoint.
	sf::Font font_; //stores the font the text should be rendered with.
	float numSides_; //stores the number of sides the checkpoint uses.
	float width_, height_; //stores the width and heigh of the checkpoint.
	sf::ConvexShape shape_;
	sf::Vector2f pos_;
	std::vector<sf::Vector2f> points_;
	Player::Shape playerShape_; //Stores the players shape for when they are needed to be respawned.
	sf::Vector2f playerPos_; //Stores the players posistion for when they are needed for spawning.
public:
	bool collected_; //Will tell if the player has collected the checkpoint.
	bool used_; //If the player has already been reset using the checkpoint they will not be reset and will be brought to the end game screen.
	CheckPoint(float Width, float Height, sf::Vector2f pos);
	~CheckPoint();
	void ResetPlayer(Player* p); //resets the player with the shape and posistion the checkPoint stores. Only happens after the CheckPoint has been collected once.
	void ResetCheckPoint(); //resets the CheckPoint to before it was collected or used.
	void Draw(sf::RenderWindow &w); //renders the checkpoint and text.
	void SetPos(sf::RenderWindow &w); //sets the posistion of the checkpoint and inturn the text.
	void Update(float time); //checks if the checkpoint has been collected and update the level time text if the player has not yet collected it.
	void SetColor(sf::Color color); //sets the color of the checkpoint and text.
	sf::Vector2f GetPos();  //gets the screen posistion of the checkpoint.
	sf::ConvexShape getShape(); //returns the shape.
	bool collision(Player* p); // Checks for basic collision with the player.Uses shape bounds and intersection to tell when there is a collision and returns a bool of the result.
	float distanceTo(sf::Vector2f pos); //calulates the distance to a passed posistion from the checkpoints location.
};
#endif
