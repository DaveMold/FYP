#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

//includes
#include <vector>
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <SFML/Audio.hpp>


class AudioManager {
private:
	static AudioManager* mInstance;
	AudioManager();
	std::vector<std::pair<sf::SoundBuffer*, std::string >> buffer_;
	std::vector<std::pair<sf::Sound, std::string >> sounds_;
	const int numberOfSounds = 3;

public:
	static AudioManager* instance();
	void LoadFromFile(std::string path, std::string id);
	void loadAudio();
	void PlayTrack(std::string s, bool looped);
	void SetTrackIsLooped(bool looped, std::string s);
	void SetSoundPos(sf::Vector2f pos, std::string s);
};
#endif
