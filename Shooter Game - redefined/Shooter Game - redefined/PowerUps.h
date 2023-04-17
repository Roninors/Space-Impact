#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
#include "Level.h"
using namespace sf;

class PowerUps {

public:
	PowerUps(std::string healthImgPath, std::string dbFireImgPath, std::string shieldImgPath,RenderWindow& window) {
	
		if (!healthTexture.loadFromFile(healthImgPath))
			throw "health texture not found";

		if (!doubleFireTexture.loadFromFile(dbFireImgPath))
			throw "health texture not found";

		if (!shieldTexture.loadFromFile(shieldImgPath))
			throw "health texture not found";
			
		healthPowerUp.setTexture(healthTexture);
	
		doubleFire.setTexture(doubleFireTexture);
		shield.setTexture(shieldTexture);
		healthPowerUp.setPosition(window.getSize().x, (rand() % int(window.getSize().y - healthPowerUp.getGlobalBounds().height)));
	}
	void drawHealthPowerUp(RenderWindow& window) {
		window.draw(healthPowerUp);
	}
	void drawDoubleFirePowerUp(RenderWindow& window) {
		window.draw(doubleFire);
	}
	
	void drawShieldPowerUp(RenderWindow& window) {
		window.draw(shield);
	}

	void powerUpMovement(RenderWindow& window, Level& levelInstance) {
	
		healthPowerUp.move(-1.5f,0.f);
		doubleFire.move(-1.5f, 0.f);
		shield.move(-1.5f, 0.f);

		if (healthPowerUp.getPosition().x <= 0)
			levelInstance.setSpawnHealth(false);

	}

	
	Sprite getHealthSprite() {
		return healthPowerUp;
	}



private:

	Sprite healthPowerUp;
	Sprite doubleFire;
	Sprite shield;

	Texture healthTexture;
	Texture doubleFireTexture;
	Texture shieldTexture;


};