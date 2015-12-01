#include "Level.h"
#include "InputManager.h"

Level::Level(sf::RenderWindow &w) {
	player = new Player(25,4, sf::Vector2f(370,100));
	platforms.push_back(new Platform(454, 54, 4, sf::Vector2f(125,300)));
	platforms.push_back(new Platform(354, 54, 4, sf::Vector2f(450, 200)));
	/*platforms.push_back(new Platform(54, 4, sf::Vector2f(300, 300)));
	platforms.push_back(new Platform(54, 4, sf::Vector2f(375, 300)));
	platforms.push_back(new Platform(54, 4, sf::Vector2f(450, 300)));
	platforms.push_back(new Platform(54, 4, sf::Vector2f(525, 300)));
	platforms.push_back(new Platform(54, 4, sf::Vector2f(600, 300)));
	platforms.push_back(new Platform(50, 3, sf::Vector2f(375, 225)));*/
}

#define FIND_KEY(key) std::find( begin, end, key ) != end //find a key in a vector	(tidies Update method)
void Level::Update(sf::Vector2f g, sf::RenderWindow &w) {

	std::vector<sf::String> const& keys = InputManager::instance()->getKeys();

	auto begin = keys.begin();
	auto end = keys.end();

	//look for the C Key in vector of keys pressed
	if (FIND_KEY("End"))
	{
		//change color of all objects
		player->SetColor(sf::Color::Red);
		for (auto itr = platforms.begin(); itr != platforms.end(); itr++)
		{
			(*itr)->SetColor(sf::Color::Blue);
		}
	}

	
	
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
}

void Level::Draw(sf::RenderWindow &w) {
	for (auto itr = platforms.begin(); itr != platforms.end(); itr++)
	{
		(*itr)->Draw(w);
	}
	player->Draw(w);
}
