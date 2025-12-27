#pragma once
#include<SFML/Graphics.hpp>
class Bird
{
private:
	//niz tekstura (2), 1 za pticu gore, jedan za odlje
	sf::Texture textures[2];
	const int gravity;
	const int flap_speed;
	float velocity_y;
	//anim counter i texture switch za mahanje krilima ptice kada ide gore i dolje
	int anim_counter, texture_switch;
	bool should_fly;
	sf::Sprite bird_sprite;
public:
	sf::Sprite get_sprite() {
		return bird_sprite;
	}
	Bird();
	void setShouldFly(bool);
	void flapBird(sf::Time&);
	void resetBirdPosition();
	void update(sf::Time&);
	float getRightBound(); // detektcija kolizije pomocu x koordinata
};
