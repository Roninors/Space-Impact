#pragma once
#include <iostream>

class Level {
public:
	Level() {
		level = 1;
		enemyShoot = false;
		detectEnemyMissile = false;
	}


	void levelChecker(int killCount, Enemy& enemyInstance) {
		switch (level) {
		case 1:
			if (killCount == 3) {
				enemyInstance.setEnemyVelocity(-1.f);
				enemyInstance.setEnemyDuration(50);
			}
			else if (killCount == 10) {
			//spawn boss
				detectEnemyMissile = true;
				enemyShoot = true;
			}
			break;
		
		}
	}

	bool getShootFlag() {
		return enemyShoot;
	}

	bool getdetectionMissiles() {
		return detectEnemyMissile;
	}


private:
	int level;
	bool enemyShoot;
	bool detectEnemyMissile;
};