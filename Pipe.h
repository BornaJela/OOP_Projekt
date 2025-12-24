#pragma once
#include <SFML/Graphics.hpp>
class Pipe
{
public:
	Pipe(int);
	sf::Sprite sprite_pipe_up, sprite_pipe_down;
	static void LoadTextures();
	void update(sf::Time& delta_time);
	float getBound();
private:
	static sf::Texture pipe_down, pipe_up;
	static int pipe_distance, move_speed;

};

