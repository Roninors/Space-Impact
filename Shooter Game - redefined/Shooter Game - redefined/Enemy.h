#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
#include <iostream>
#include <vector>
using namespace sf;
class Enemy {
public:
	
	
	Enemy(std::string imgPath) {
		if (!enemyTexture.loadFromFile(imgPath))
			throw  "can't load png";
		enemyForm.setTexture(enemyTexture);
	
		 enemyVelocity = -.5f;
		 
		 enemyTextureSize = enemyTexture.getSize();
		 enemyTextureSize.x /= 1;
		 enemyTextureSize.y /= 5;


	}

	



	void enemySpawn( RenderWindow &window, std::vector<Sprite>& enemies) {
		
			enemyForm.setPosition(window.getSize().x, (rand() % int(window.getSize().y - enemyForm.getGlobalBounds().height)));
			enemies.push_back(Sprite(enemyForm));
		
	}

	void enemyMovement(RenderWindow &window, std::vector<Sprite>& enemies, int imageCount) {
	
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].move(enemyVelocity, 0.f);

			enemies[i].setTextureRect(IntRect(enemyTextureSize.x * 0 , enemyTextureSize.y * imageCount, enemyTextureSize.x, enemyTextureSize.y)); 
			//delete enemies when out of screen
			if (enemies[i].getPosition().x <= 0 || enemies[i].getPosition().y >= window.getSize().y)
				enemies.erase(enemies.begin() + i);


		};
		

		}


	void drawEnemy(RenderWindow &window, std::vector<Sprite> enemies) {

		for (int i = 0; i < enemies.size(); i++) {
			window.draw(enemies[i]);

		}
	}
	
	int getEnemySpawnTimer() {
		return enemySpawnTimer;
	}

	int getEnemySpawnDuration() {
		return enemySpawnDuration;
	}
	int getEnemyImageCount() {
		return enemyImageCount;
	}
	void setEnemyImageCount() {
		enemyImageCount++;
	}

	void resetEnemyImageCount() {
		enemyImageCount = 0;
	}

	void setEnemySpawnTimer() {
		enemySpawnTimer++;
	}

	void resetEnemySpawnTimer() {
		enemySpawnTimer = 0;
	}
	
	void setEnemyVelocity(int speed) {
		enemyVelocity = speed;
	}

	void setEnemyDuration(int duration) {
		enemySpawnDuration = duration;
	}


private:
	Texture enemyTexture;
	Sprite enemyForm;
	float enemyVelocity = 0;
	Vector2u enemyTextureSize;
	int enemySpawnTimer = 0;
	int enemySpawnDuration = 100;
	int enemyImageCount = 0;
};