#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
using namespace sf;

class BossMissile {
public:
	BossMissile() {}

	BossMissile(std::string missileImgPath) {
		if (!bossMissileTexture.loadFromFile(missileImgPath))
			throw "boss missile img not found";

		bossMissileForm.setTexture(bossMissileTexture);

		bossMissileTextureSize = bossMissileTexture.getSize();

		bossMissileTextureSize.x /= 6;

		bossMissileTextureSize.y /=  1;

		bossMissileForm.setScale(Vector2f(.5f, .5f));

		bossShootTimer = 0;
		bossShootDuration = 30;
		bossMissileVelocity = -10.f;
	
	}


	void bossMissilesMovement(RenderWindow& window, std::vector<Sprite>& bossMissiles) {

		for (int i = 0; i < bossMissiles.size(); i++) {
			bossMissileForm.setPosition(bossCenterPosition);
			bossMissiles[i].move(bossMissileVelocity, 0.0f);

			//delete enemy missiles when out of screen
			if (bossMissiles[i].getPosition().x <= 0)
				bossMissiles.erase(bossMissiles.begin() + i);


		};


	}


	void bossShootMissiles(std::vector<Sprite>& bossMissiles) {
		if (bossShootTimer < bossShootDuration) {
			bossShootTimer++;
		}


		if (bossShootTimer >= bossShootDuration) {



			bossMissiles.push_back(Sprite(bossMissileForm));

			bossShootTimer = 0;
		}
	}

	void drawEnemyMissile(RenderWindow& window, std::vector<Sprite>& bossMissiles) {
		for (int i = 0; i < bossMissiles.size(); i++) {
			window.draw(bossMissiles[i]);

		};
	}

	void setBossMissilePosition(float x_axis, float y_axis) {
		bossCenterPosition = Vector2f(x_axis, y_axis);
	}


private:
	Vector2u bossMissileTextureSize;
	int bossShootTimer = 0;
	int bossShootDuration = 0;
	Sprite bossMissileForm;
	Texture bossMissileTexture;
	Vector2f bossCenterPosition;
	float bossMissileVelocity = 0;
};