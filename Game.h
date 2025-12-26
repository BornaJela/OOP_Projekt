#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Bird.h"
#include "Pipe.h"
#include <random>
#include <vector>
class Game
{
public:
	//klasa game sa svojim konstruktorom
	Game(sf::RenderWindow& window);
	sf::RenderWindow& win;
	//funkcija za pokretanje igre
	void start_game();
private:
	//klasa texture za pozadinsku sliku
	sf::Texture background_texture, ground_texture;
	sf::Sprite background_sprite, ground_sprite_first, ground_sprite_second;
	sf::Clock clock;
	int move_speed = 200;
	void draw_img();
	void move_ground(sf::Time& delta_time);
	Bird bird;
	bool is_space_pressed,run_game;
	void Process(sf::Time& delta_time);
	int pipe_counter, pipe_spawn_time;
	void check_collision();
	std::vector<Pipe> pipes;
	std::random_device random;
	//250 min, 550 je max
	std::uniform_int_distribution<int> dist{ 250,550 };
	void reset_game();
};

