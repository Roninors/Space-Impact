#pragma once
#include <iostream>
#include "BossMissile.h"
#include "Boss.h"
class Level {
public:
	

	Level() {
		level = 1;
		enemyShoot = false;
		detectEnemyMissile = false;
		bossShoot = false;
		detectBossMissiles = false;
	}


	void levelChecker(int killCount, Enemy& enemyInstance, Boss& bossInstance, BossMissile& bossMissileInstance) { 
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
			else if (killCount == 2) {
				enemyInstance.setEnemyVelocity(-2.f);

				detectEnemyMissile = true;
				enemyShoot = true;
				spawnBoss = true;
				bossShoot = true;
				detectBossMissiles = true;
			
			
			}
			
			if (bossInstance.getBossHp() <= 98) {

				std::cout << "detect";
				bossMissileInstance.setBossShootDuration(10);
			}

			break;
		
		}
	}

	bool getDetectionBossMissiles() {
		return detectBossMissiles;
	
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

	bool getBossShoot() {
		return bossShoot;
	}

	

private:
	int level;
	bool enemyShoot;
	bool detectEnemyMissile;
	bool spawnBoss;
	bool bossShoot;
	bool detectBossMissiles;
};