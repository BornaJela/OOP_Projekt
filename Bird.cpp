#include "Bird.h"
#include "Globals.h"
Bird::Bird():gravity(10),flap_speed(250),velocity_y(0),animation_counter(0),texture_switch(0)
,fly(false){
	textures[0].loadFromFile("images and sounds for game/birddown.png");
	textures[1].loadFromFile("images and sounds for game/birdup.png");
	bird_sprite.setTexture(textures[0]);
	bird_sprite.setScale(SCALE_FACTOR,SCALE_FACTOR);
	reset_position();
}

void Bird::shouldfly(bool fly) {
	this->fly = fly;
}
void Bird::flap(sf::Time& delta_time) {
	velocity_y = -flap_speed * delta_time.asSeconds();
}
void Bird::reset_position() {
	bird_sprite.setPosition(100, 50);
	velocity_y = 0;
}
void Bird::update_position(sf::Time& delta_time) {
	if (bird_sprite.getGlobalBounds().top < 570.5 && shouldfly) {
		if (animation_counter == 5) {
			bird_sprite.setTexture(textures[texture_switch]);
			if (texture_switch)texture_switch = 0;
			else texture_switch = 1;
			animation_counter = 0;
		}
		animation_counter++;
		velocity_y += gravity*delta_time.asSeconds();
		bird_sprite.move(0, velocity_y);
		if (bird_sprite.getGlobalBounds().top < 0) {
			bird_sprite.setPosition(100,0);
		}
	}
}
float Bird::get_bound() {
	return bird_sprite.getGlobalBounds().left + bird_sprite.getGlobalBounds().width;
}
