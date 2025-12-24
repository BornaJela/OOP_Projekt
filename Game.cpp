#include "Game.h"
#include "Globals.h"
#include "Pipe.h"
#include <iostream>
//konstruktor za game
Game::Game(sf::RenderWindow& window) : win(window),is_space_pressed(false)
,run_game(true),pipe_counter(71),pipe_spawn_time(70){
	background_texture.loadFromFile("images and sounds for game/bg.png");
	//postavljanje spritea na sliku, odnosno slika (background image) postaje sprite
	background_sprite.setTexture(background_texture);
	//scale-amo ga da se poravna sa slikom i koristimo predefinirani scale_factor
	background_sprite.setScale(SCALE_FACTOR,SCALE_FACTOR);
	background_sprite.setPosition(0, -100);

	ground_texture.loadFromFile("images and sounds for game/ground.png");
	ground_sprite_first.setTexture(ground_texture);
	ground_sprite_second.setTexture(ground_texture);
	ground_sprite_first.setScale(SCALE_FACTOR, SCALE_FACTOR);
	ground_sprite_second.setScale(SCALE_FACTOR, SCALE_FACTOR);

	//pozicija dobivena kao  -> visina ekrana - (visina poda * scale factor)
	ground_sprite_first.setPosition(0, 600.5);
	//na prvi sprite se drugi samo nastavlja dok god je potrebno (do kraja igre)
	ground_sprite_second.setPosition(ground_sprite_first.getGlobalBounds().width,600.5);
	Pipe::LoadTextures();
}
void Game::Process(sf::Time& delta_time)
{
	if (is_space_pressed) {
		move_ground(delta_time);
		if (pipe_counter > pipe_spawn_time) {
			pipes.push_back(Pipe(dist(random)));
			pipe_counter = 0;
		}
		pipe_counter++;
		for (int i = 0; i < pipes.size(); i++) {
			pipes[i].update(delta_time);	
			//ako prodje ekran da ga izbrise
			if (pipes[i].getBound() < 0) {
				pipes.erase(pipes.begin() + i);
			}
		}
	}
	bird.update_position(delta_time);
	check_collision();
}
void Game::start_game() {
	win.setFramerateLimit(60);
	sf::Clock clock;
	//pokrece se kod i otvara se prozor
	while (win.isOpen()) {
		sf::Event event;
		sf::Time delta_time = clock.restart();
		//ova ispod se vrti sve dok je prozor otvoren, odnosno dok ne ugasimo
		while (win.pollEvent(event)) {

			//ako je njegov tip "closed", zatvori prozor
			if (event.type == sf::Event::Closed) {
				win.close();
			}
			//pokretanje na space
			if (event.type == sf::Event::KeyPressed && run_game) {
				if (event.key.code == sf::Keyboard::Space) {
					is_space_pressed = false;
					bird.shouldfly(false);
					bird.flap(delta_time);
				}
			}
		}
		Process(delta_time);
		draw_img();
		//zaslon
		win.display();
	}
}
void Game::check_collision() {
	if (pipes.size() > 0) {
		if (pipes[0].sprite_pipe_down.getGlobalBounds().intersects(bird.get_sprite().getGlobalBounds()) ||
			pipes[0].sprite_pipe_up.getGlobalBounds().intersects(bird.get_sprite().getGlobalBounds()) ||
			bird.get_sprite().getGlobalBounds().top >= 580) {
			is_space_pressed = false;
			run_game = false;
		}
	}
}
void Game::draw_img() {
	for (Pipe& p : pipes) {
		win.draw(p.sprite_pipe_down);
		win.draw(p.sprite_pipe_up);
	}
	win.draw(background_sprite);
	win.draw(ground_sprite_first);
	win.draw(ground_sprite_second);
	win.draw(bird.get_sprite());
}
void Game::move_ground(sf::Time& delta_time) {
	//pod se pomjera ulijevo, zato -move_speed pomnozeno sa vremenom koje je proslo
	//vece vrijeme=igra ide brze
	//0 je y koordinata
	ground_sprite_first.move(-move_speed * delta_time.asSeconds(), 0);
	ground_sprite_second.move(-move_speed * delta_time.asSeconds(), 0);
	//ako je prisa svoju duzinu, nova mu je odmah nakon sprite2
	if (ground_sprite_first.getGlobalBounds().left + ground_sprite_first.getGlobalBounds().width < 0) {

		ground_sprite_first.setPosition(ground_sprite_second.getGlobalBounds().left + 
			ground_sprite_second.getGlobalBounds().width,600.5);
	}
	if (ground_sprite_second.getGlobalBounds().left + ground_sprite_second.getGlobalBounds().width < 0) {

		ground_sprite_second.setPosition(ground_sprite_first.getGlobalBounds().left +
			ground_sprite_first.getGlobalBounds().width, 600.5);
	}
}
