#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{
public:
	//klasa game sa svojim konstruktorom
	Game(sf::RenderWindow& window);
	sf::RenderWindow& win;
	//funkcija za pokretanje igre
	void start_game();

};

