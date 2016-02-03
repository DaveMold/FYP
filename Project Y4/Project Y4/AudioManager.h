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
	std::vector<std::pair<sf::SoundBuffer, std::string >> buffer;
	sf::Sound sound;
public:
	static AudioManager* instance();
	void loadAudio();
	void PlayTrack(std::string s);
};
#endif
