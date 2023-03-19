#pragma once
#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
#include <iostream>
#include <vector>
using namespace sf;
class Collision {
public:
    Collision() {
        killCount = 0;
    }
  
   
	void enemy_missileCollision(std::vector <Sprite>& missiles, std::vector <Sprite>& enemies) {
        for (int i = 0; i < missiles.size(); i++) {
            for (int k = 0; k < enemies.size(); k++) {


                if (missiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds())) {
                    enemies.erase(enemies.begin() + k);
                    missiles.erase(missiles.begin() + i);
                    killCount++;
                    std::cout << killCount << " ";
                    break;
                }

            }
        }
	}

    void enemy_playerCollision(std::vector <Sprite>& enemies,Sprite player) {
        for (int j = 0; j < enemies.size(); j++) {
            if (player.getGlobalBounds().intersects(enemies[j].getGlobalBounds()))
                enemies.erase(enemies.begin() + j);

            
        }
    };
private:
    int killCount;
};

