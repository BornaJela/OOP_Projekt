#include "Pipe.h"
#include "Globals.h"

Pipe::Pipe(int y_pos)
{
	sprite_pipe_down.setTexture(pipe_down);
	sprite_pipe_up.setTexture(pipe_up);
	sprite_pipe_down.setScale(SCALE_FACTOR, SCALE_FACTOR);
	sprite_pipe_up.setScale(SCALE_FACTOR, SCALE_FACTOR);
	sprite_pipe_up.setPosition(WIN_WIDTH, y_pos);
	sprite_pipe_down.setPosition(WIN_WIDTH, y_pos - pipe_distance + sprite_pipe_down.getGlobalBounds().height);
}

void Pipe::LoadTextures()
{
	pipe_up.loadFromFile("images and sounds for game/pipe.png");
	pipe_down.loadFromFile("images and sounds for game/pipedown.png");

}

void Pipe::update(sf::Time& delta_time)
{
	sprite_pipe_up.move(-move_speed * delta_time.asSeconds(),0);
	sprite_pipe_down.move(-move_speed * delta_time.asSeconds(), 0);

}

float Pipe::getBound()
{
	return sprite_pipe_down.getGlobalBounds().left + sprite_pipe_down.getGlobalBounds().width;
}
sf::Texture Pipe::pipe_up, Pipe::pipe_down;
int Pipe::pipe_distance=100, Pipe::move_speed=400;