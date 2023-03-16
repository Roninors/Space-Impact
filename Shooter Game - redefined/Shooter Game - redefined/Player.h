#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
#include <iostream>
#include <vector>
using namespace sf;
class Player {
public:
	Player() {
	
	}

	Player(std::string imgPath) {
		if (!playerTexture.loadFromFile(imgPath))
			throw  "can't load png";
		playerSprite.setTexture(playerTexture);
		playerSprite.setScale(Vector2f(.1f, .1f));
	}

	void drawPlayer(RenderWindow &window) {
		window.draw(playerSprite);
	}

	void movePlayer(RenderWindow &window) {
		playerSprite.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
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
private:
	Texture playerTexture;
	Sprite playerSprite;
};