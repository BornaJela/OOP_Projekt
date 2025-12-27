#pragma once
#include<SFML/Graphics.hpp>
#include"Bird.h"
#include<vector>
#include"Pipe.h"
#include <fstream>
#include<random>
class Game
{
public:
	Game(sf::RenderWindow&);
	sf::RenderWindow& win;
	void startGameLoop();
private:
	int high_score;
	sf::Text high_score_text;
	//spriteovi i teksture za pticu i tlo
	sf::Texture bg_texture, ground_texture;
	sf::Sprite bg_sprite, ground_sprite1, ground_sprite2;
	Bird bird;
	//igra se pokrece na enter
	bool is_enter_pressed, run_game, start_monitoring;
	const int move_speed = 270; //-> moguce promjeniti ako je brzina prevelika
	virtual void draw();
	void moveGround(sf::Time&);
	void doProcessing(sf::Time& dt);
	void checkCollisions();
	void restartGame();
	void checkScore();
	// broj pretvara u string, korisno za pratiti rezultat ptice
	std::string toString(int);
	int pipe_counter, pipe_spawn_time, score;
	std::vector<Pipe> pipes;
	//generator randoma
	std::random_device rd;
	// funkcija iz biblioteke koj generira random broj izmedju 2 navedena, koristimo za cijevi
	std::uniform_int_distribution<int> dist{ 250,550 }; 
	sf::Font font;
	sf::Text restart_text, score_text;
	void loadHighScore();
	void saveHighScore();
};

