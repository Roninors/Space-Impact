#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
using namespace sf;
#include <iostream>
#include <vector>



class Boss {
public:
	Boss() {}

	

	Boss(std::string bossImgPath, RenderWindow &window) {
		if (!bossTexture.loadFromFile(bossImgPath))
			throw "boss img not found";

		bossSprite.setTexture(bossTexture);
		bossTextureSize = bossTexture.getSize();

		bossSprite.setPosition(window.getSize().x, window.getSize().y - 300);
		bossTextureSize.x /= 1;
		bossTextureSize.y /= 44;
		bool spawnBoss = false;

		 bossLevel = 1;
		 bossHp = 100;


	}
	
	void bossAnimator(RenderWindow &window,bool spawnBoss) {
		if (spawnBoss == true)
		{
			drawBossLife = true;
			bossSprite.setTextureRect(IntRect(bossTextureSize.x * 0, bossTextureSize.y * bossImgCount, bossTextureSize.x, bossTextureSize.y));
		}
		
	}

	void bossMovement(RenderWindow &window, bool spawnBoss) {
		if (spawnBoss == true) {
		
			if (bossSprite.getPosition().x > window.getSize().x - 150) {
				bossSprite.move(-.5f, 0.f);

			}
		}
			
	}

	void drawBoss(RenderWindow &window) {
		window.draw(bossSprite);
	}

	int getBossImgCount() {
		return bossImgCount;
	}

	void setBossImgCount() {
		bossImgCount++;
	}
	
	void resetBossImgCount() {
		bossImgCount = 0;
	
	}

	Sprite getBossSprite() {
		return bossSprite;
	}
	
	void setBossHp(int hpReducer) {
		bossHp -= hpReducer;
	}
	
	void bossHpChecker() {
		if (bossHp == 0) {
			deadDecider = true;
			drawBossLife = false;
			bossLevel++;
		};
		
	}

	void bossLevelChecker() {
		if (bossLevel == 2) {
			bossHp = 150;
		}
	}

	int getBossHp() {
		return bossHp;
	}

	bool getBossDeadDecider() {
		return deadDecider;
	}

	int getBossLevel() {
		return bossLevel;
	}
private:
	Sprite bossSprite;
	Texture bossTexture;
	Vector2u bossTextureSize;
	int bossImgCount = 0;
	int bossLevel = 0;
	int bossHp = 0;
	bool deadDecider = false;
	bool drawBossLife = false;
		
};



