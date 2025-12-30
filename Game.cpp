#include "Game.h"
#include"Globals.h"
#include<sstream>
//inicijalizacija sa member list, win je clan game.h sa referencom na window
Game::Game(sf::RenderWindow& window) : win(window),
is_enter_pressed(false),
run_game(true),
start_monitoring(false), // pracenje score-a
pipe_counter(71), // brojac za spawnanje cijevi, 71 jer u originalnom se spawna svako 1.2s (70/60)
pipe_spawn_time(70), // kada pipe_counter dostigne ovaj spawn time, cijev se stvori
score(0), high_score(0), sound()
{
	win.setFramerateLimit(60);
	bg_texture.loadFromFile("assets/bg.png");
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
	bg_sprite.setPosition(0.f, -250.f);

	ground_texture.loadFromFile("assets/ground.png");
	ground_sprite1.setTexture(ground_texture);
	ground_sprite2.setTexture(ground_texture);

	ground_sprite1.setScale(SCALE_FACTOR, SCALE_FACTOR);
	ground_sprite2.setScale(SCALE_FACTOR, SCALE_FACTOR);

	ground_sprite1.setPosition(0, 578);
	ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().width, 578);

	font.loadFromFile("assets/Flappy-Bird.ttf");
	restart_text.setFont(font);
	restart_text.setCharacterSize(48);
	restart_text.setFillColor(sf::Color::Black);
	restart_text.setPosition(120, 650);
	restart_text.setString("RESTART GAME!!");

	score_text.setFont(font);
	score_text.setCharacterSize(70);
	score_text.setFillColor(sf::Color::White);
	score_text.setPosition(270, 15);
	score_text.setString("0");

	high_score_text.setFont(font);
	high_score_text.setCharacterSize(20);
	high_score_text.setFillColor(sf::Color::Yellow);
	high_score_text.setPosition(15,10 );
	high_score_text.setString("HIGH SCORE: 0");


	Pipe::loadTextures();
	Game::loadHighScore();

}

void Game::doProcessing(sf::Time& dt)
{
	if (is_enter_pressed)
	{
		moveGround(dt);

		if (pipe_counter > pipe_spawn_time)
		{
			//generiranje random pozicija (brojeva)
			pipes.push_back(Pipe(dist(rd)));
			pipe_counter = 0;
		}
		pipe_counter++;

		for (int i = 0; i < pipes.size(); i++)
		{
			pipes[i].update(dt);
			//ako je cijev izasla iz ekrana, izbrisi je
			if (pipes[i].getRightBound() < 0)
			{
				pipes.erase(pipes.begin() + i);
			}
		}

		checkCollisions();
		checkScore();
	}
	bird.update(dt);
}
void Game::startGameLoop()
{
	sf::Clock clock;
	//Game Loop
	while (win.isOpen())
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		//Event Loop
		while (win.pollEvent(event))
		{
			//ako se klikne x, izadji
			if (event.type == sf::Event::Closed)
			{
				win.close();
			}
			//koristi space samo dok run_game odnosno dok je igra upaljena
			if (event.type == sf::Event::KeyPressed && run_game)
			{
				//enter pokrece igru ako igra vec nije pokrenuta
				if (event.key.code == sf::Keyboard::Enter && !is_enter_pressed)
				{
					is_enter_pressed = true;
					bird.setShouldFly(true);
				}
				//skace na space ako je aktivna igra
				if (event.key.code == sf::Keyboard::Space && is_enter_pressed)
				{
					sound.playFlap();
					bird.flapBird(dt);
				}
			}
			//kada igra zavrsi, pojavi se restart game koji mozemo aktivirati pritiskom misa
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !run_game)
			{
				//klik unutar teksta
				if (restart_text.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					restartGame();
				}

			}
		}

		doProcessing(dt);


		draw();
		//pokreni prozor
		win.display();
	}
}

void Game::checkCollisions()
{
	// 3 nacina za game-over, ili je sudar s donjom ili s gornjom cijevi ili dodir sa tlom
	if (pipes.size() > 0)
	{
		if (pipes[0].sprite_down.getGlobalBounds().intersects(bird.get_sprite().getGlobalBounds()) ||
			pipes[0].sprite_up.getGlobalBounds().intersects(bird.get_sprite().getGlobalBounds()) ||
			bird.get_sprite().getGlobalBounds().top >= 540)
		{
			is_enter_pressed = false;
			run_game = false;
			sound.playHit();
		}
	}
}

void Game::checkScore()
{
	if (pipes.size() > 0)
	{
		// pocinje tek kada prodje prvu cijev
		if (!start_monitoring)
		{
			//ako je lijeva strana ptice presla lijevu stranu cijevi,a desna strana
			// ptice je manja od desne cijevi, znaci da je ptica izmedju cijevi
			if (bird.get_sprite().getGlobalBounds().left > pipes[0].sprite_down.getGlobalBounds().left &&
				bird.getRightBound() < pipes[0].getRightBound())
			{
				start_monitoring = true;
			}
		}
		//dok se uvjet iznad izvrsava, ptica je u cijevi, kada izadje, tek onda joj se score poveca
		else
		{
			if (bird.get_sprite().getGlobalBounds().left > pipes[0].getRightBound())
			{
				sound.playScore();
				score++;
				score_text.setString("" + toString(score));
				if (score > high_score) {
					high_score = score;
					high_score_text.setString("High score: " + toString(high_score));
					saveHighScore();
				}
				start_monitoring = false;
			}
		}
	}
}
void Game::draw()
{
	win.draw(bg_sprite);
	for (Pipe& pipe : pipes)
	{
		win.draw(pipe.sprite_down);
		win.draw(pipe.sprite_up);
	}
	win.draw(ground_sprite1);
	win.draw(ground_sprite2);
	win.draw(bird.get_sprite());
	win.draw(score_text);
	//da cijeli tekst dobijenu neku sjenu (da je sto slicniji font originalnom Flappy bird-u)
	sf::Text shadow = score_text;
	shadow.setFillColor(sf::Color(0, 0, 0, 128));
	shadow.setPosition(score_text.getPosition().x + 2, score_text.getPosition().y + 2);
	win.draw(shadow);
	win.draw(score_text);
	sf::Text high_shadow = high_score_text;
	high_shadow.setFillColor(sf::Color(0, 0, 0, 128));
	high_shadow.setPosition(high_score_text.getPosition().x + 2, high_score_text.getPosition().y + 2);

	win.draw(high_shadow);
	win.draw(high_score_text);
	if (!run_game)
	{
		win.draw(restart_text);
	}

}

void Game::moveGround(sf::Time& dt)
{
	ground_sprite1.move(-move_speed * dt.asSeconds(), 0.f);
	ground_sprite2.move(-move_speed * dt.asSeconds(), 0.f);
	//2 uvjeta za beskonacno dno, kada prvo zavrsi, ide iduce, a nakon iduceg ide opet prvo
	if (ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width < 0)
	{
		ground_sprite1.setPosition(ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width, 578);
	}
	if (ground_sprite2.getGlobalBounds().left + ground_sprite2.getGlobalBounds().width < 0)
	{
		ground_sprite2.setPosition(ground_sprite1.getGlobalBounds().left + ground_sprite1.getGlobalBounds().width, 578);
	}

}

void Game::restartGame()
{
	bird.resetBirdPosition();
	bird.setShouldFly(false);
	run_game = true;
	is_enter_pressed = false;
	pipe_counter = 71;
	pipes.clear();
	score = 0;
	score_text.setString("0");

}

std::string Game::toString(int num)
{
	//stringstreamanje za konverziju integera u string
	std::stringstream ss;
	ss << num;
	return ss.str();
}
void Game::loadHighScore() {
	std::ifstream file("highscore.txt");
	if (file.is_open()) {
		file >> high_score;
		file.close();
		high_score_text.setString("High score: " + toString(high_score));
	}
}
void Game::saveHighScore(){
	std::ofstream file("highscore.txt");
	if (file.is_open()) {
		file << high_score;
		file.close();
	}
}