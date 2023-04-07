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
class EnemyMissile {
public:
	EnemyMissile() {}

	EnemyMissile(std::string imgPath) {
	
		if (!enemyMissileTexture.loadFromFile(imgPath))
			throw "cannot find image";

		enemyMissileForm.setTexture(enemyMissileTexture);
		enemyMissileForm.setScale(Vector2f(.5f, .5f));

		enemyShootTimer = 0;
		enemyShootDuration = 30;
		enemyMissileVelocity = -10.f;
	}

	void missilesMovement(RenderWindow& window, std::vector<Sprite>& enemyMissiles) {

		for (int i = 0; i < enemyMissiles.size(); i++) {
			enemyMissileForm.setPosition(enemyCenterPosition);
			enemyMissiles[i].move(enemyMissileVelocity, 0.0f);

			//delete enemy missiles when out of screen
			if (enemyMissiles[i].getPosition().x <= 0)
				enemyMissiles.erase(enemyMissiles.begin() + i);


		};

		
	}

	
	void enemyShootMissiles(std::vector<Sprite>& enemyMissiles) {
		if (enemyShootTimer < enemyShootDuration) {
			enemyShootTimer++;
		}
		
		
		if (enemyShootTimer >= enemyShootDuration) {
			
				
			
			enemyMissiles.push_back(Sprite(enemyMissileForm));

			enemyShootTimer = 0;
		}
	}

	void drawEnemyMissile(RenderWindow &window, std::vector<Sprite>& enemyMissiles) {
		for (int i = 0; i < enemyMissiles.size(); i++) {
			window.draw(enemyMissiles[i]);

		};
	}

	void setEnemyMissilePosition(float x_axis, float y_axis) {
		enemyCenterPosition = Vector2f(x_axis, y_axis);
	}


private:

	int enemyShootTimer=0;
	int enemyShootDuration=0;
	Sprite enemyMissileForm;
	Texture enemyMissileTexture;
	Vector2f enemyCenterPosition;
	float enemyMissileVelocity = 0;

};