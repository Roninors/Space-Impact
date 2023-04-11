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


	void levelChecker(int killCount, Enemy& enemyInstance, Boss& bossInstance, BossMissile& bossMissileInstance, bool bossDied) { 
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
			else if (killCount == 30) {

				enemyInstance.setEnemyVelocity(-2.f);
				detectEnemyMissile = true;
				spawnBoss = true;
				bossShoot = true;
				detectBossMissiles = true;
			
			}
			
			if (bossInstance.getBossHp() <= 50) {
				bossMissileInstance.setBossShootDuration(10);
			}


			if (bossDied == true) {
				spawnBoss = false;
				bossShoot = false;
				detectBossMissiles = false;
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

	void setDetectionMissiles(bool showDecider) {
		 detectEnemyMissile = showDecider;
	}


	void setSpawnBoss(bool showDecider) {
		 spawnBoss = showDecider;
	}

	void setBossShoot(bool showDecider) {
		 bossShoot = showDecider;
	}
	

private:
	int level;
	bool enemyShoot;
	bool detectEnemyMissile;
	bool spawnBoss;
	bool bossShoot;
	bool detectBossMissiles;
};