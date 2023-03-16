#pragma once

#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
#include <iostream>
#include <vector>
using namespace sf;
class Missile {
public:
	Missile() {}

	Missile(std::string imgPath) {
		if (!missileTexture.loadFromFile(imgPath))
			throw "can't load png file";

		bulletForm.setTexture(missileTexture);
		bulletForm.setScale(Vector2f(.05f, .05f));
	}

	void missilesMovement(RenderWindow &window, float missileVelocity, std::vector<Sprite>& missiles) {
	
		for (int i = 0; i < missiles.size(); i++) {
			missiles[i].move(missileVelocity, 0.0f);

			if (missiles[i].getPosition().x >= window.getSize().x)
				missiles.erase(missiles.begin() + i);


		};
	}
	void shootMissiles(Vector2f centerPosition, std::vector<Sprite>& missiles) {

		bulletForm.setPosition(centerPosition);
		missiles.push_back(Sprite(bulletForm));
	}

	void drawMissiles(RenderWindow &window, std::vector<Sprite> missiles) {
	
		for (int i = 0; i < missiles.size(); i++) {
			window.draw(missiles[i]);

		};
	}

	 
private:
	Texture missileTexture;
	Sprite bulletForm;

};