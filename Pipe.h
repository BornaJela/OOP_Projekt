#pragma once
#include<SFML/Graphics.hpp>
class Obstacle {
public:
	virtual~Obstacle(){}
	virtual float getRightBound() = 0;
};
class Pipe:public Obstacle
{
public:
	Pipe(int);
	sf::Sprite sprite_up, sprite_down;
	static void loadTextures();
	void update(sf::Time&);
	float getRightBound() override;

private:
	static sf::Texture texture_down, texture_up;
	static int pipe_distance, move_speed;
};
