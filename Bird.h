#pragma once
#include <SFML/Graphics.hpp>

class Bird
{
private:
	sf::Texture textures[2];
	const int flap_speed;
	const int gravity;
	float velocity_y;
	int animation_counter, texture_switch;
	bool fly;
public:
	sf::Sprite bird_sprite;
	Bird();
	const sf::Sprite& get_sprite()const { return bird_sprite; }
	void shouldfly(bool);
	void flap(sf::Time& delta_time);
	void reset_position();
	void update_position(sf::Time& delta_time);
	float get_bound();
};

