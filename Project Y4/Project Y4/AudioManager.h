#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

//includes
#include <vector>
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <SFML/Audio.hpp>
#include <assert.h>


class AudioManager {
private:
	static AudioManager* mInstance; //used for creating an instance of the class so the object can be acessed from any where.
	AudioManager();//Constructor
	std::vector<std::pair<sf::SoundBuffer*, std::string >> buffer_; //stores the sound files in buffers.
	std::vector<std::pair<sf::Sound, std::string >> sounds_; //store 3 sounds to be used by the audio manager to play from a buffer.
	const int numberOfSounds = 3; //stores the sounds count limit.

public:
	static AudioManager* instance(); //get the instance or create a new one if one dose not egsist. 
	void LoadFromFile(std::string path, std::string id); //loads the buffers with the sounds from the file
	void loadAudio(); // calls the loadFromFile with the correct paths.
	void PlayTrack(std::string s, bool looped); //looks for an available sound and plays the track.
	void SetTrackIsLooped(bool looped, std::string s); // sets the track to loop or not.
	void SetSoundPos(sf::Vector2f pos, std::string s);  //sets the sounds posisiton for spacial audio.
};
#endif
