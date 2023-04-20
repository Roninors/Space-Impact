#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
#include <iostream>
#include <vector>
#include "Boss.h"
#include "Level.h"
#include "Missile.h"
using namespace sf;
class Collision {
public:
    Collision(std::string collisionImg) {
        
        if (!explosionTexture.loadFromFile(collisionImg))
            throw  "can't load png";
        
        explosionTextureSize = explosionTexture.getSize();
        explosionTextureSize.x /= 1;
        explosionTextureSize.y /= 8;
        hit = false;
        killCount = 0;
        explosionFrame.setTexture(explosionTexture);
    }
  

public:
  
    void drawExplosion(RenderWindow &window, Clock clock) {

        if (hit)
        {
            if (clock.getElapsedTime().asMilliseconds() < 500) {
                explosionFrame.setTextureRect(IntRect(explosionTextureSize.x * 0, explosionTextureSize.y * explosionAnimation, explosionTextureSize.x, explosionTextureSize.y));
                window.draw(explosionFrame);
            }
       
        }
         
    }


   
	void enemy_missileCollision(std::vector <Sprite>& missiles, std::vector <Sprite>& enemies, RenderWindow& window, std::vector <Sprite>& enemyMissiles) {
      
        for (int i = 0; i < missiles.size(); i++) {
            for (int k = 0; k < enemies.size(); k++) {
             
                
                    if (missiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds())) {

                        explosionFrame.setPosition(Vector2f(enemies[k].getPosition().x, enemies[k].getPosition().y));
                        hit = true;
                        enemies.erase(enemies.begin() + k);
                        missiles.erase(missiles.begin() + i);
                        killCount++;
                        

                        break;
                    
                   
                    }

            }
        }

     


	}

    



    void detectEnemyMissile(std::vector<Sprite>& enemyMissiles, std::vector<Sprite>& missiles) {
        for (int k = 0; k < missiles.size(); k++) {

            for (int i = 0; i < enemyMissiles.size(); i++) {



                if (enemyMissiles[i].getGlobalBounds().intersects(missiles[k].getGlobalBounds())) {

                    explosionFrame.setPosition(Vector2f(enemyMissiles[i].getPosition().x, enemyMissiles[i].getPosition().y));
                    hit = true;
                    enemyMissiles.erase(enemyMissiles.begin() + i);
                    missiles.erase(missiles.begin() + k);
                    break;
                }



            };


        };


    }


    void enemy_playerCollision(std::vector <Sprite>& enemies, Sprite player, Player& playerInstance) {

        for (int j = 0; j < enemies.size(); j++) {
            if (player.getGlobalBounds().intersects(enemies[j].getGlobalBounds())) {
                playerInstance.setHp(1);
                explosionFrame.setPosition(Vector2f(enemies[j].getPosition().x, enemies[j].getPosition().y));
                
                hit = true;
                enemies.erase(enemies.begin() + j);
            
            }

        }

    }

    void player_EnemyMissileCollision(std::vector <Sprite>& enemyMissiles, Sprite player, Player& playerInstance) {

        for (int j = 0; j < enemyMissiles.size(); j++) {
            if (player.getGlobalBounds().intersects(enemyMissiles[j].getGlobalBounds())) {
                playerInstance.setHp(1);
                explosionFrame.setPosition(Vector2f(player.getPosition().x, player.getPosition().y));

                hit = true;
                enemyMissiles.erase(enemyMissiles.begin() + j);

            }

        }
    }


    void detectBossMissiles(std::vector<Sprite>& bossMissiles, std::vector<Sprite>& missiles) {
    
        for (int k = 0; k < missiles.size(); k++) {

            for (int i = 0; i < bossMissiles.size(); i++) {



                if (bossMissiles[i].getGlobalBounds().intersects(missiles[k].getGlobalBounds())) {

                    explosionFrame.setPosition(Vector2f(bossMissiles[i].getPosition().x, bossMissiles[i].getPosition().y));
                    hit = true;
                    bossMissiles.erase(bossMissiles.begin() + i);
                    missiles.erase(missiles.begin() + k);
                    break;
                }



            };


        };
    }

    void player_BossMissileCollision(std::vector <Sprite>& bossMissiles, Sprite player, Player& playerInstance) {
    
        for (int j = 0; j < bossMissiles.size(); j++) {
            if (player.getGlobalBounds().intersects(bossMissiles[j].getGlobalBounds())) {
                playerInstance.setHp(1);
                explosionFrame.setPosition(Vector2f(player.getPosition().x, player.getPosition().y));

                hit = true;
                bossMissiles.erase(bossMissiles.begin() + j);

            }

        }
    }

    void boss_PlayerMissileCollision(std::vector<Sprite>& missiles, Sprite bossSprite, Boss& bossInstance) {
    
       


            for (int i = 0; i < missiles.size(); i++) {



                if (missiles[i].getGlobalBounds().intersects(bossSprite.getGlobalBounds())) {

                    explosionFrame.setPosition(Vector2f(bossSprite.getPosition().x, bossSprite.getPosition().y));
                    hit = true;
                    missiles.erase(missiles.begin() + i);
                    bossInstance.setBossHp(1);
                
                }



            };

           

        
    }

    
    void powerUpCollision(std::vector<Sprite>& missiles, Player& playerInstance, std::vector<Sprite>& heartPowerup, std::vector<Sprite>& ammo,Missile& missileInstance) {

        for (int i = 0; i < missiles.size(); i++) {

            for (int j = 0; j < heartPowerup.size(); j++) {
            
            
                if (missiles[i].getGlobalBounds().intersects(heartPowerup[j].getGlobalBounds())) {

                    explosionFrame.setPosition(Vector2f(heartPowerup[j].getPosition().x, heartPowerup[j].getPosition().y));
                    hit = true;
                    missiles.erase(missiles.begin() + i);
                    heartPowerup.erase(heartPowerup.begin() + j);
                    playerInstance.addHp(2);
                    break;
                }
            
            }

        };

        for (int i = 0; i < missiles.size(); i++) {

            for (int j = 0; j < ammo.size(); j++) {


                if (missiles[i].getGlobalBounds().intersects(ammo[j].getGlobalBounds())) {

                    explosionFrame.setPosition(Vector2f(ammo[j].getPosition().x, ammo[j].getPosition().y));
                    hit = true;
                    missiles.erase(missiles.begin() + i);
                    ammo.erase(ammo.begin() + j);
                    missileInstance.setShootDuration();
                    break;
                }

            }

        };
    }

    void setHit(bool flag) {
        hit = flag;
    }

    bool getHit() {
        return hit;
    }

    void setExplosionAnimation() {
        explosionAnimation++;
    }

    int getExplosionAnimation() {
        return explosionAnimation;
    }

    void resetExplosionAnimation() {
        explosionAnimation = 0;
    }

    int getKillCount() {
        return killCount;
    }




private:
    Sprite explosionFrame;
    Texture explosionTexture;
    Vector2u explosionTextureSize;
    int killCount;
    std::vector <Sprite> explosionVector;
    bool hit;
    int explosionAnimation = 0;
};

