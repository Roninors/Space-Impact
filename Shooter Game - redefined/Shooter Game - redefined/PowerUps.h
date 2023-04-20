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


		doubleFire.setScale(.2, .2);
		
	}
	void drawHealthPowerUp(RenderWindow& window, std::vector<Sprite>& heartPowerup) {
		for (int i = 0; i < heartPowerup.size(); i++) {
			window.draw(heartPowerup[i]);

		}
		
	}
	void drawDoubleFirePowerUp(RenderWindow& window, std::vector<Sprite>& ammo) {

		for (int i = 0; i < ammo.size(); i++) {
			window.draw(ammo[i]);

		}

	}
	
	void drawShieldPowerUp(RenderWindow& window) {
		window.draw(shield);
	}

	void powerUpMovement(RenderWindow& window, Level& levelInstance, std::vector<Sprite>& heartPowerup, std::vector<Sprite>& ammo) {
		for (int i = 0; i < heartPowerup.size(); i++) {
			heartPowerup[i].move(-1.5f, 0.f);

			
			//delete heart when out of screen
			if (heartPowerup[i].getPosition().x <= 0 )
				heartPowerup.erase(heartPowerup.begin() + i);


		};
		
		for (int i = 0; i < ammo.size(); i++) {
			ammo[i].move(-1.5f, 0.f);


			//delete heart when out of screen
			if (ammo[i].getPosition().x <= 0)
				ammo.erase(ammo.begin() + i);


		};

		shield.move(-1.5f, 0.f);

		

	}

	void spawnHealth(RenderWindow& window, std::vector<Sprite>& heartPowerup) {
		healthPowerUp.setPosition(window.getSize().x, (rand() % int(window.getSize().y - healthPowerUp.getGlobalBounds().height)));
		heartPowerup.push_back(Sprite(healthPowerUp));
	}
	
	void spawnRpFire(RenderWindow& window, std::vector<Sprite>& ammo) {
		doubleFire.setPosition(window.getSize().x, (rand() % int(window.getSize().y - doubleFire.getGlobalBounds().height)));
		ammo.push_back(Sprite(doubleFire));
	}

	int getFireSpawnTimer() {
		return fireSpawnTimer;
	}

	int getFireSpawnDuration() {
		return fireSpawnDuration;
	}


	void setFireSpawnTimer() {
		fireSpawnTimer++;
	}

	void resetFireSpawnTimer() {
		fireSpawnTimer = 0;
	}




	int getHealthSpawnTimer() {
		return healthSpawnTimer;
	}

	int getHealthSpawnDuration() {
		return healthSpawnDuration;
	}
	

	void setHealthSpawnTimer() {
		healthSpawnTimer++;
	}

	void resetHealthSpawnTimer() {
		healthSpawnTimer = 0;
	}


private:

	Sprite healthPowerUp;
	Sprite doubleFire;
	Sprite shield;

	Texture healthTexture;
	Texture doubleFireTexture;
	Texture shieldTexture;

	int healthSpawnTimer = 0;
	int healthSpawnDuration = 2800;

	int fireSpawnTimer = 0;
	int fireSpawnDuration = 2500;

};