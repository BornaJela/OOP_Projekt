#include "Bird.h"
#include "Globals.h"
//konstruktor
Bird::Bird():gravity(10),flap_speed(250),velocity_y(0),animation_counter(0),texture_switch(0)
,fly(false){
	//ucitavanje slika i scaleanje
	textures[0].loadFromFile("images and sounds for game/birddown.png");
	textures[1].loadFromFile("images and sounds for game/birdup.png");
	bird_sprite.setTexture(textures[0]);
	bird_sprite.setScale(SCALE_FACTOR,SCALE_FACTOR);
	reset_position();
}
//boolean s privatnom varijablom ako ptica leti
void Bird::shouldfly(bool fly) {
	this->fly = fly;
}
//letenje (micanje krila), -flap jer je kretanje ka gori i mnozi se sa sekundama da se konstantno minjaju
void Bird::flap(sf::Time& delta_time) {
	velocity_y = -flap_speed * delta_time.asSeconds();
}
//pocetna pozicija ptice
void Bird::reset_position() {
	bird_sprite.setPosition(100, 50);
	velocity_y = 0;
}
void Bird::update_position(sf::Time& delta_time) {
	//animacija ptice za mijenjanje krila, svako 5 frameova
		if (animation_counter == 5) {
			bird_sprite.setTexture(textures[texture_switch]);
			if (texture_switch)texture_switch = 0;
			else texture_switch = 1;
			animation_counter = 0;
		}
		animation_counter++;

		//fizika kako ce brzo padat
		velocity_y += gravity*delta_time.asSeconds();
		bird_sprite.move(0, velocity_y);
		//gornja granica da ne bi ptica izasla
		if (bird_sprite.getGlobalBounds().top < 0) {
			bird_sprite.setPosition(100,0);
			velocity_y = 0;
		}
		//donja granica da ne ode ispod
		if (bird_sprite.getGlobalBounds().top > 570.5) {
			bird_sprite.setPosition(100, 570.5);
			velocity_y = 0;
		}
	}
//koristit ce se za pozociju ptice da bi se registrirala kolizija sa cijevima
float Bird::get_bound() {
	return bird_sprite.getGlobalBounds().left + bird_sprite.getGlobalBounds().width;
}
