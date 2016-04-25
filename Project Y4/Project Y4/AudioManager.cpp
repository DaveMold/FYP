#include "AudioManager.h"

AudioManager* AudioManager::mInstance = nullptr;
AudioManager::AudioManager() {
	for (int i = 0; i < numberOfSounds; i++) {
		sf::Sound s;
		std::pair<sf::Sound, std::string> s_pair = std::make_pair(s, "Empty");
		sounds_.push_back(s_pair);
	}
}

AudioManager* AudioManager::instance() {
	if (mInstance == nullptr)
	{
		mInstance = new AudioManager();
	}
	return mInstance;
}

void AudioManager::LoadFromFile(std::string path, std::string id) {
	sf::SoundBuffer* soundB = new sf::SoundBuffer();
	soundB->loadFromFile(path);
	std::pair<sf::SoundBuffer*, std::string> sB_pair = std::make_pair(soundB,id);
	buffer_.push_back(sB_pair);
}

void AudioManager::loadAudio() {
	LoadFromFile("Assets/Audio/Background.wav", "Background");
	LoadFromFile("Assets/Audio/menuBoop.wav", "menuBoop");
	LoadFromFile("Assets/Audio/Select.wav", "Select");
	LoadFromFile("Assets/Audio/Death.wav","Death");
	LoadFromFile("Assets/Audio/EndLevel.wav","EndLevel");
	LoadFromFile("Assets/Audio/Jump.wav","Jump");
	LoadFromFile("Assets/Audio/JumpPannel.wav","JumpPannel");
	LoadFromFile("Assets/Audio/SwapPoint.wav","SwapPoint");
}

void AudioManager::PlayTrack(std::string s, bool looped) {
	std::vector<std::pair<sf::Sound, std::string >>::iterator itrA = sounds_.begin();
	assert(s != "");  // assert that string != ""; abort() if string is empty.
	assert(itrA != sounds_.end()); // asset that bool != NULL; about() if string is Null.
	for (; itrA < sounds_.end(); itrA++)
	{
		if (sf::Sound::Status::Stopped == (*itrA).first.getStatus())
		{
			(*itrA).second = "Empty";
		}
	}
	itrA = sounds_.begin();
	assert(itrA != sounds_.end()); // asset that bool != NULL; about() if string is Null.
	for (; itrA < sounds_.end(); itrA++)
	{
		std::pair<sf::Sound, std::string > temp = (*itrA);
		if ("Empty" == temp.second)
		{
			std::vector<std::pair<sf::SoundBuffer*, std::string >>::iterator itrB = buffer_.begin();
			assert(itrB != buffer_.end()); // asset that buffer != NULL; about() if string is Null.
			for (; itrB < buffer_.end(); itrB++)
			{
				if ((*itrB).second == s)
				{
					if (s == "Background")
						temp.first.setVolume(35);
					temp.first.setBuffer(*(*itrB).first);
					temp.second = s;
					temp.first.play();
					temp.first.setLoop(looped);
					*itrA = temp;
					return;
				}
			}
		}
	}
}

void AudioManager::SetTrackIsLooped(bool looped, std::string s) {
	for (auto itr = sounds_.begin(); itr < sounds_.end(); itr++)
	{
		if (s == (*itr).second)
		{
			(*itr).first.setLoop(looped);
		}
	}
}

void AudioManager::SetSoundPos(sf::Vector2f pos, std::string s) {
	for (auto itr = sounds_.begin(); itr < sounds_.end(); itr++)
	{
		if (s == (*itr).second)
		{
			(*itr).first.setMinDistance(100);
			(*itr).first.setAttenuation(0.05f);
			(*itr).first.setPosition(sf::Vector3f(pos.x,pos.y,0));
		}
	}
}