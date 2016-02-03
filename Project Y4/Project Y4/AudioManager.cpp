#include "AudioManager.h"

AudioManager* AudioManager::mInstance = nullptr;
AudioManager::AudioManager() {

}

AudioManager* AudioManager::instance() {
	if (mInstance == nullptr)
	{
		mInstance = new AudioManager();
	}

	return mInstance;
}

void AudioManager::loadAudio() {
	sf::SoundBuffer b;
	b.loadFromFile("Assets/Audio/menuBoop.wav");
	buffer.push_back(std::make_pair(b, "menuBoop"));
	b.loadFromFile("Assets/Audio/Select.wav");
	buffer.push_back(std::make_pair(b, std::string("Select")));
	b.loadFromFile("Assets/Audio/Death.wav");
	buffer.push_back(std::make_pair(b, sf::String("Death")));
	b.loadFromFile("Assets/Audio/EndLevel.wav");
	buffer.push_back(std::make_pair(b, sf::String("EndLevel")));
	b.loadFromFile("Assets/Audio/Jump.wav");
	buffer.push_back(std::make_pair(b, sf::String("Jump")));
	b.loadFromFile("Assets/Audio/JumpPannel.wav");
	buffer.push_back(std::make_pair(b, sf::String("JumpPannel")));
	b.loadFromFile("Assets/Audio/SwapPoint.wav");
	buffer.push_back(std::make_pair(b, sf::String("SwapPoint")));
}

void AudioManager::PlayTrack(std::string s) {
	for (int i = 0; i < buffer.size(); i++)
	{
		if (s == buffer[i].second)
		{
			sound.setBuffer(buffer[i].first);
			sound.play();
		}
	}
}