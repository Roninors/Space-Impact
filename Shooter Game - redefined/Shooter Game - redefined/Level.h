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
		hitSpawn = true;
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

			if (bossInstance.getBossHp() <= 50 && hitSpawn) {

				spawnHealth = true;
			}
			else {
				spawnHealth = false;
			}


			if (bossDied == true) {
				spawnBoss = false;
				bossShoot = false;
				detectBossMissiles = false;
				enemyInstance.setEnemyVelocity(-1.5f);
				detectEnemyMissile = false;
				enemyShoot = false;
				level++;
			}

		
			break;
		
		case 2:


			break;
		}
	}
	
	bool getSpawnHealth() {
		return spawnHealth;
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

	void setSpawnHealth(bool spawnDecider) {
		spawnHealth = spawnDecider;
	}
	

	void setHitSpawnHealth(bool decider) {
	
		hitSpawn = decider;
	}

private:
	int level;
	bool enemyShoot;
	bool detectEnemyMissile;
	bool spawnBoss;
	bool bossShoot;
	bool detectBossMissiles;
	bool spawnHealth;
	bool spawnShield;
	bool spawnDbFire;
	bool hitSpawn;
};