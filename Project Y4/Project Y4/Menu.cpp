#include "Menu.h"
#include "InputManager.h"

Menu::Menu(std::pair<float, float> windowDesmentions): showSettings(false), preset(PRESETONE), gameOn(false), Exit(false) {
	textures.reserve(9);
	textures[0].loadFromFile("\Assets\Menu\Yes.png");
	textures[1].loadFromFile("\Assets\Menu\No.png");
	textures[2].loadFromFile("\Assets\Menu\Start.png");
	textures[3].loadFromFile("\Assets\Menu\Settings.png");
	textures[4].loadFromFile("\Assets\Menu\Exit.png");
	textures[5].loadFromFile("\Assets\Menu\Colors.png");
	textures[6].loadFromFile("\Assets\Menu\Back.png");
	textures[7].loadFromFile("\Assets\Menu\Preset1.png");
	textures[8].loadFromFile("\Assets\Menu\Preset2.png");

	//sprites.reserve(8);
	for (int i = 0; i < textures.size(); i++)
	{
		sprites[i].first.setTexture(textures[i]);
		if (i != 2)
			sprites[i].second = false;
		else
			sprites[i].second = true;
	}

	arrowHeadTexture.loadFromFile("\Assets\Menu\ArrowHead.png");
	arrowHeadSprite.setTexture(arrowHeadTexture);

	//main menu
	sprites[2].first.setPosition(windowDesmentions.first/4, windowDesmentions.second / 2.0f);
	sprites[3].first.setPosition(windowDesmentions.first/4, sprites[2].first.getPosition().y + 50);
	sprites[4].first.setPosition(windowDesmentions.first/4, sprites[3].first.getPosition().y + 50);
	//settings menu
	sprites[5].first.setPosition((windowDesmentions.first / 4.0f) * 3.0f, windowDesmentions.second / 2.0f);
	sprites[7].first.setPosition(sprites[5].first.getPosition().x + sprites[6].first.getGlobalBounds().width, windowDesmentions.second / 2.0f);
	sprites[8].first.setPosition(sprites[5].first.getPosition().x + sprites[6].first.getGlobalBounds().width, windowDesmentions.second / 2.0f);
	sprites[6].first.setPosition(sprites[5].first.getPosition().x, windowDesmentions.second / 2.0f);
}

Menu::~Menu(){

}

#define FIND_KEY(key) std::find( begin, end, key ) != end //find a key in a vector	(tidies Update method)
void Menu::Update() {
	std::vector<sf::String> const& keys = InputManager::instance()->getKeys();

	auto begin = keys.begin();
	auto end = keys.end();

	if (FIND_KEY("Up"))
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites[i].second)
			{
				sprites[i].second = false;
				if (i < 2)
				{
					if (i = 0)
						sprites[1].second = true;
					else
						sprites[0].second = true;
				}
				else if (i > 1 && i < 5)
				{
					if (i == 2)
						sprites[4].second = true;
					if (i == 3)
						sprites[2].second = true;
					if (i == 4)
						sprites[3].second = true;
				}
				else if (i == 5 || i == 6)
				{
					if (i == 5)
						sprites[6].second = true;
					if (i == 6)
						sprites[5].second = true;
				}
			}
		}
	}
	if (FIND_KEY("Enter"))
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites[i].second)
			{
				if (i == 2)
					gameOn = true;
				else if (i == 3)
				{
					showSettings = true;
					sprites[i].second = false;
					sprites[5].second = true;
				}
				else if (i == 4)
				{
					Exit = true;
					//sprites[0].second = true;
				}
				else if (i == 5)
				{
					if (preset == PRESETONE)
						preset = PRESETTWO;
					if (preset == PRESETTWO)
						preset = PRESETONE;
				}
				else if (i == 6)
					sprites[2].second = true;
			}
		}
	}
}

void Menu::Draw(sf::RenderWindow &w) {

	for (int i = 0; i < sprites.size(); i++)
	//This loop will set the posistion of the arrowHead to be pointing at the selected menu selection.
	{
		if (sprites[i].second)
			arrowHeadSprite.setPosition(sprites[i].first.getPosition().x /*- sprites[i].first.getGlobalBounds().width / 2.0f*/ - arrowHeadSprite.getGlobalBounds().width,
				sprites[i].first.getPosition().y);
	}

	w.draw(arrowHeadSprite);

	for (int i = 2; i < sprites.size(); i++)
	{
		w.draw(sprites[i].first);
	}

	if (showSettings)
	{
		w.draw(sprites[5].first);
		w.draw(sprites[6].first);
		switch (preset)
		{
		case PRESETONE:
			w.draw(sprites[7].first);
			break;
		case PRESETTWO:
			w.draw(sprites[8].first);
			break;
		}
	}


}