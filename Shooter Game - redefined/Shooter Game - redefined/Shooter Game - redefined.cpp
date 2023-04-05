#include"SFML\System.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"
#include"SFML\Window.hpp"
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include "Missile.h"
#include "Level.h"
#include "EnemyMissile.h"
using namespace sf;



int main()
{
    RenderWindow window(VideoMode(700, 500), "Space Impact");
    
    window.setFramerateLimit(60);
  

    Texture bgTexture;
    Sprite backGround;

    if (!bgTexture.loadFromFile("textures/background.png"))
        throw  "can't load png";

    backGround.setTexture(bgTexture);
    backGround.setScale(1.1f, 1.1f);

  

   
    std::vector <Sprite> enemies;
    std::vector <Sprite> missiles;
    std::vector <Sprite> enemyMissiles;

    //Collision
    Collision collision("textures/explode.png");

    //player
    Player userPlayer("textures/Ligher.png");

    
    //missile
    Missile missile("textures/06.png");


    //enemy
    Enemy enemy("textures/purpleShip.png");

    //Level
    Level level;
    
    //enemy missile
    EnemyMissile enemyMissile("textures/06.png");
    
   //timer
    Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }


        // update
        

        //player movement
        userPlayer.movePlayer(window);

        //position for center missile
        
        missile.setCenterPosition(userPlayer.getPlayer().getPosition().x +10, userPlayer.getPlayer().getPosition().y +10 );
   
        userPlayer.updateAnimation();

       
        //animation changer
        if (clock.getElapsedTime().asSeconds() > .1f) {
            enemy.setEnemyImageCount();
            userPlayer.setPlayerAnimation();

            if (collision.getHit() == true) {
                collision.setExplosionAnimation();
            }
          
            clock.restart();
           
        }
         
      
       
        if (userPlayer.getPlayerAnimation() == 4) {
        
            userPlayer.resetPlayerAnimation();
        }
           

        if (enemy.getEnemyImageCount() == 4) {

            enemy.resetEnemyImageCount();
        }

        if (collision.getExplosionAnimation() == 8) {
          
            collision.resetExplosionAnimation();
            collision.setHit(false);
        }

     
        


            
        //trigger
       missile.shootMissiles(missiles);
        
         //missile/projectile projection

        missile.missilesMovement(window, missiles);

        //enemy spawn 

        if (enemy.getEnemySpawnTimer() < enemy.getEnemySpawnDuration())
            enemy.setEnemySpawnTimer();

        if (enemy.getEnemySpawnTimer() >= enemy.getEnemySpawnDuration()) {
            enemy.enemySpawn(window,enemies);
            enemy.resetEnemySpawnTimer();
        }
        
        //enemy movement
        enemy.enemyMovement(window,enemies, enemy.getEnemyImageCount());

        //shoot enemy missile
        enemyMissile.enemyShootMissiles(enemyMissiles);

        //enemy missile projection
        enemyMissile.missilesMovement(window, enemyMissiles);
        for (int i = 0; i < enemies.size(); i++) {
            enemyMissile.setEnemyMissilePosition(enemies[i].getPosition().x, enemies[i].getPosition().y);
        }


        //detection for collision of projectiles and enemies
        collision.enemy_missileCollision(missiles, enemies,window,enemyMissiles);

        //collision for enemies and player
        collision.enemy_playerCollision(enemies, userPlayer.getPlayer(), userPlayer,enemyMissiles);

        // collision for enemy missiles and player missiles
        if (level.getdetectionMissiles() == true) {
            std::cout << "detect";
            collision.detectEnemyMissile(enemyMissiles, missiles);
        }
      
        //
        
        
        //check player hp
        userPlayer.hpChecker(window);

        level.levelChecker(collision.getKillCount(), enemy);

        window.clear();
     

        //draw animations

        window.draw(backGround);

        enemy.drawEnemy(window, enemies);

        userPlayer.drawPlayer(window);

        missile.drawMissiles(window,missiles);

        collision.drawExplosion(window, clock);

        if (level.getShootFlag() == true) {
            enemyMissile.drawEnemyMissile(window, enemyMissiles);
        }

        window.display();
    }

}

