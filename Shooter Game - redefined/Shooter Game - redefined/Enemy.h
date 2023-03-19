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
		enemyForm.setScale(Vector2f(.2f, .2f));
		 enemyVelocity = -.5f;

	}

	void enemySpawn( RenderWindow &window, std::vector<Sprite>& enemies) {
		
			enemyForm.setPosition(window.getSize().x, (rand() % int(window.getSize().y - enemyForm.getGlobalBounds().height)));
			enemies.push_back(Sprite(enemyForm));
		
	}

	void enemyMovement(RenderWindow &window, std::vector<Sprite>& enemies) {
	
		for (int i = 0; i < enemies.size(); i++) {
			enemies[i].move(enemyVelocity, 0.f);

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
	
	
	
private:
	Texture enemyTexture;
	Sprite enemyForm;
	float enemyVelocity = 0;


};