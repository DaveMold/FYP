#include "Level.h"
#include "InputManager.h"

Level::Level(sf::RenderWindow &w) {
	player = new Player(25,4, sf::Vector2f(370,100));
	platforms.push_back(new Platform(50, 4, sf::Vector2f(150,300)));
	/*platforms.push_back(new Platform(50, 4, sf::Vector2f(225, 300)));
	platforms.push_back(new Platform(50, 4, sf::Vector2f(300, 300)));
	platforms.push_back(new Platform(50, 4, sf::Vector2f(375, 300)));
	platforms.push_back(new Platform(50, 4, sf::Vector2f(450, 300)));
	platforms.push_back(new Platform(50, 4, sf::Vector2f(525, 300)));
	platforms.push_back(new Platform(50, 4, sf::Vector2f(600, 300)));*/
	platforms.push_back(new Platform(50, 3, sf::Vector2f(375, 225)));
}

#define FIND_KEY(key) std::find( begin, end, key ) != end //find a key in a vector	(tidies Update method)
void Level::Update(sf::Vector2f g, sf::RenderWindow &w) {

	std::vector<sf::String> const& keys = InputManager::instance()->getKeys();

	auto begin = keys.begin();
	auto end = keys.end();

	//look for the Left Arrow Key in vector of keys pressed
	if (FIND_KEY("G"))
	{
		if (g.y > 0)
			g.y = 0;
		else
			g.y = -0.9;
	}

	player->Update(g);
	
	for (auto itr = platforms.begin(); itr != platforms.end(); itr++)
	{
		(*itr)->Update();
		if (player->Collision(w, (*itr)).first)
			player->SetColor(sf::Color::Red);
		else
			player->SetColor(sf::Color::Blue);
	}
}

void Level::Draw(sf::RenderWindow &w) {
	for (auto itr = platforms.begin(); itr != platforms.end(); itr++)
	{
		(*itr)->Draw(w);
	}
	player->Draw(w);
}
