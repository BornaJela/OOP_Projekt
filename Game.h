#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Bird.h"
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
};

