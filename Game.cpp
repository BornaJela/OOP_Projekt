#include "Game.h"
#include "Globals.h"
#include <iostream>
//konstruktor za game
Game::Game(sf::RenderWindow& window) : win(window),is_space_pressed(false),run_game(true){
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
			if (event.type == sf::Event::KeyPressed && run_game) {
				if (event.key.code == sf::Keyboard::Space) {
					is_space_pressed = true;
					bird.shouldfly(true);
				}
			}
		}
		move_ground(delta_time);
		draw_img();
		bird.update_position(delta_time);
		//zaslon
		win.display();
	}
}
void Game::draw_img() {
	win.draw(background_sprite);
	win.draw(ground_sprite_first);
	win.draw(ground_sprite_second);
	win.draw(bird.bird_sprite);
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
