#include "Pipe.h"
#include "Globals.h"
Pipe::Pipe(int y_pos)
{
	sprite_down.setTexture(texture_down);
	sprite_up.setTexture(texture_up);

	sprite_down.setScale(SCALE_FACTOR, SCALE_FACTOR);
	sprite_up.setScale(SCALE_FACTOR, SCALE_FACTOR);	

	sprite_up.setPosition(WIN_WIDTH, y_pos);
	sprite_down.setPosition(WIN_WIDTH, y_pos - pipe_distance + sprite_up.getGlobalBounds().height);
}

void Pipe::LoadTextures()
{
	texture_down.loadFromFile("images and sounds for game/piped.png");
	texture_up.loadFromFile("images and sounds for game/pipe.png");

}

void Pipe::update(sf::Time& delta_time)
{
	sprite_up.move(-move_speed * delta_time.asSeconds(),0);
	sprite_down.move(-move_speed * delta_time.asSeconds(), 0);

}

float Pipe::getBound()
{
	return sprite_down.getGlobalBounds().left + sprite_down.getGlobalBounds().width;
}
sf::Texture Pipe::texture_down, Pipe::texture_up;
int Pipe::pipe_distance = 100, Pipe::move_speed = 400;