#ifndef	LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Platform.h"

class Level {
private:
	Player* player;
	std::vector<Platform*> platforms;
public:
	Level(sf::RenderWindow &w);
	void Update(sf::Vector2f g, sf::RenderWindow &w);
	void Draw(sf::RenderWindow &w);

};
#endif