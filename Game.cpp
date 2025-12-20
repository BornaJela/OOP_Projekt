#include "Game.h"
#include <iostream>
Game::Game(sf::RenderWindow& window) : win(window){

}
void Game::start_game() {
	//zakljucaj fps
	win.setFramerateLimit(60);
	//pokrece se kod i otvara se prozor
	while (win.isOpen()) {
		sf::Event event;
		//ova ispod se vrti sve dok je prozor otvoren, odnosno dok ne ugasimo
		while (win.pollEvent(event)) {
			//ako je njegov tip "closed", znaci da smo zatvorili prozor
			if (event.type == sf::Event::Closed) {
				win.close();
			}
		}
		win.clear(sf::Color::Black);
		//zaslon
		win.display();
	}
}
