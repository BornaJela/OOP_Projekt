#include "Sound.h"
#include <iostream>
Sound::Sound() :masterVolume(30.0f),flapVolume(12.0f),scoreVolume(21.0f),hitVolume(30.0f) {
	loadSound();
}
void Sound::loadSound() {
	flapBuffer.loadFromFile("assets/flap.wav");
	scoreBuffer.loadFromFile("assets/score.wav");
	hitBuffer.loadFromFile("assets/dead.wav");

	flapSound.setBuffer(flapBuffer);
	scoreSound.setBuffer(scoreBuffer);
	hitSound.setBuffer(hitBuffer);
}
//setter za zvuk, svaki ima razlicit
void Sound::setMasterVolume(float vol) {
	masterVolume = vol;
	flapSound.setVolume(masterVolume * 0.4f);
	scoreSound.setVolume(masterVolume * 0.7f);
	hitSound.setVolume(masterVolume * 1.0f);
}
void Sound::playFlap() {
	//dodano jer je zvuk malo kasnija, isto u sve 3
	flapSound.stop();
	flapSound.setPlayingOffset(sf::Time::Zero);
	flapSound.play();
}
void Sound::playScore() {
	//dodano jer je zvuk malo kasnija, isto u sve 3
	scoreSound.stop();
	scoreSound.setPlayingOffset(sf::Time::Zero);
	scoreSound.play();
}
void Sound::playHit() {
	//dodano jer je zvuk malo kasnija, isto u sve 3
	hitSound.stop();
	hitSound.setPlayingOffset(sf::Time::Zero);
	hitSound.play();
}
