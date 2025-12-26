#pragma once
#include <SFML/Graphics.hpp>
class Pipe
{
public:
	Pipe(int);
	sf::Sprite sprite_up, sprite_down;
	static void LoadTextures();
	void update(sf::Time& delta_time);
	float getBound();
private:
	static sf::Texture texture_down, texture_up;
	static int pipe_distance, move_speed;

};

