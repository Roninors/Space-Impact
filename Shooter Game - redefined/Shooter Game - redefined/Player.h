#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
#include <iostream>
#include <vector>
#include <windows.h>
using namespace sf;
class Player {
public:
	Player() {
		

	}

	Player(std::string imgPath) {
		if (!playerTexture.loadFromFile(imgPath))
			throw  "can't load png";
		playerSprite.setTexture(playerTexture);
		textureSize = playerTexture.getSize();
		textureSize.x /= 1;
		textureSize.y /= 4;
		hp = 3;
	
	}
	

	void updateAnimation() {
	
		playerSprite.setTextureRect(IntRect(textureSize.x * 0, textureSize.y * playerAnimation, textureSize.x, textureSize.y));
	};
	

	void drawPlayer(RenderWindow &window) {
		window.draw(playerSprite);
	}

	void movePlayer(RenderWindow &window) {

		//event listener for mouse movement
		playerSprite.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);



		//player move limitations
		if (playerSprite.getPosition().y < 0)
			playerSprite.setPosition(playerSprite.getPosition().x, 0.f);

		if (playerSprite.getPosition().y > window.getSize().y - playerSprite.getGlobalBounds().height)
			playerSprite.setPosition(playerSprite.getPosition().x, window.getSize().y - playerSprite.getGlobalBounds().height);

		if (playerSprite.getPosition().x < 0)
			playerSprite.setPosition(0, playerSprite.getPosition().y);


		if (playerSprite.getPosition().x > window.getSize().x - playerSprite.getGlobalBounds().width)
			playerSprite.setPosition(window.getSize().x - playerSprite.getGlobalBounds().width, playerSprite.getPosition().y);
	}

	
	Sprite getPlayer() {
		return playerSprite;
	}

	int getPlayerHp() {
		return hp;
	}

	void hpChecker(RenderWindow& window) {
		if (hp == 0)
		{
			window.close();
		}
	}

	void setHp(int hpReducer) {
	
		hp -= hpReducer;
	}

	void setPlayerAnimation() {
		playerAnimation++;
	}
	int getPlayerAnimation() {
		return playerAnimation;
	}

	void resetPlayerAnimation() {
		playerAnimation = 0;
	}
private:
	Texture playerTexture;
	Sprite playerSprite;
	Vector2u textureSize;
	int playerAnimation = 0;
	int hp = 0;
	
};

