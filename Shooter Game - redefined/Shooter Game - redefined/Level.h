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
			if (killCount == 10) {
				enemyInstance.setEnemyVelocity(-1.f);
				enemyInstance.setEnemyDuration(50);
			}
			else if (killCount == 20) {
				enemyInstance.setEnemyVelocity(-1.8f);
				detectEnemyMissile = true;
				enemyShoot = true;
			}
			else if (killCount == 25) {
				enemyInstance.setEnemyVelocity(-2.f);
				detectEnemyMissile = true;
				enemyShoot = true;

				spawnBoss = true;
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


	bool getSpawnBoss() {
		return spawnBoss;
	}

	

private:
	int level;
	bool enemyShoot;
	bool detectEnemyMissile;
	bool spawnBoss;
};