#pragma once

#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
#include <iostream>
#include <vector>
#include "Player.h"
#include "Missile.h"
using namespace sf;
class Missile {
public:
	Missile() {}
	Missile(std::string imgPath) {
		if (!missileTexture.loadFromFile(imgPath))
			throw "can't load png file";

		bulletForm.setTexture(missileTexture);
		bulletForm.setScale(Vector2f(.5f, .5f));

		shootTimer = 0;
		shootDuration = 15;
		missileVelocity = 10.f;
	}

	void missilesMovement(RenderWindow &window, std::vector<Sprite>& missiles) {
	
		for (int i = 0; i < missiles.size(); i++) {
			missiles[i].move(missileVelocity, 0.0f);

			//delete missiles when out of screen
			if (missiles[i].getPosition().x >= window.getSize().x)
				missiles.erase(missiles.begin() + i);


		};
	}
	void shootMissiles( std::vector<Sprite>& missiles) {

		if (shootTimer < shootDuration)
			shootTimer++;

		//trigger
		if (Mouse::isButtonPressed(Mouse::Left) && shootTimer >= shootDuration) {

			bulletForm.setPosition(centerPosition);
			missiles.push_back(Sprite(bulletForm));

			shootTimer = 0;
		}
		
	}

	void drawMissiles(RenderWindow &window, std::vector<Sprite> missiles) {
	
		for (int i = 0; i < missiles.size(); i++) {
			window.draw(missiles[i]);

		};
	}

	void setCenterPosition(float x_axis, float y_axis) {
		centerPosition = Vector2f(x_axis,y_axis);

	};

	void setShootDuration() {
	
		shootDuration = 5;
	}
	
private:
	Texture missileTexture;
	Sprite bulletForm;
	Vector2f centerPosition;
	int shootTimer =0;
	int shootDuration=0;
	float missileVelocity =0;

};