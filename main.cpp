
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Game.h"
int main()
{
    //visina i sirina i ime igre
    sf::VideoMode videomode({ WIN_WIDTH, WIN_HEIGHT });
    sf::RenderWindow win(videomode,"Flappy Bird");
    Game game(win);
    game.start_game();

}