#pragma once
#include <SFML/Audio.hpp>
class Sound
{
private:
	//buffer je ko tekstura u bird.cpp
	sf::SoundBuffer flapBuffer;
	sf::SoundBuffer scoreBuffer;
	sf::SoundBuffer hitBuffer;

	// sound je ovdje kao sprite, isti postupak, 1 soundBuffer, vise zvukova umjesto da svaki koristi svoj, npr
	// SoundBuffer1 SoundBuffer2 itd.
	sf::Sound flapSound;
	sf::Sound scoreSound;
	sf::Sound hitSound;

	float masterVolume;
	float flapVolume;
	float scoreVolume;
	float hitVolume;
public:
	Sound();
	void playFlap();
	void playScore();
	void playHit();
	void loadSound();
	void setMasterVolume(float vol);
};

