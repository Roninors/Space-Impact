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
#include "Boss.h"


using namespace sf;



int main()
{
    RenderWindow window(VideoMode(700, 500), "Space Impact");
    
    window.setFramerateLimit(60);
  

    Texture bgTexture;
    Sprite backGround;


    //background
    if (!bgTexture.loadFromFile("textures/background.png"))
        throw  "can't load png";

    backGround.setTexture(bgTexture);
    backGround.setScale(1.1f, 1.1f);


    //font

    Font textFont;
    

    if (!textFont.loadFromFile("fonts/paladins3d.ttf"))
        throw "text not found";

    Text killCountText;
    killCountText.setFont(textFont);
    killCountText.setCharacterSize(20);
    killCountText.setPosition(Vector2f(125.f, 0.f));

    Text killCountLabel;
    killCountLabel.setFont(textFont);
    killCountLabel.setCharacterSize(20);
    killCountLabel.setString("Kills :");
    killCountLabel.setPosition(Vector2f(10.f, 0.f));


    Text lifeCountText;
    lifeCountText.setFont(textFont);
    lifeCountText.setCharacterSize(20);
    lifeCountText.setPosition(Vector2f(420.f, 0.f));



    Text lifeCountLabel;
    lifeCountLabel.setFont(textFont);
    lifeCountLabel.setCharacterSize(20);
    lifeCountLabel.setString("Lives :");
    lifeCountLabel.setPosition(Vector2f(300.f, 0.f));


   
    std::vector <Sprite> enemies;
    std::vector <Sprite> missiles;
    std::vector <Sprite> enemyMissiles;
    std::vector <Sprite> bossMissiles;
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
    EnemyMissile enemyMissile("textures/enemyProjectile.png");
    
   //timer
    Clock clock;

   //boss
    Boss boss("textures/boss1.png", window);

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
            boss.setBossImgCount();

            if (collision.getHit() == true) {
                collision.setExplosionAnimation();
            }
          
            clock.restart();
           
        }
         
      
       
        if (userPlayer.getPlayerAnimation() == 4) {
            
            userPlayer.resetPlayerAnimation();
        }
           


        if (boss.getBossImgCount() == 44) {

            boss.resetBossImgCount();
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

        killCountText.setString(std::to_string(collision.getKillCount()));

        //collision for enemies and player
        collision.enemy_playerCollision(enemies, userPlayer.getPlayer(), userPlayer);


        //get enemy missile detection

        if (level.getdetectionMissiles() == true) {

            // collision for enemy missiles and player missiles
            collision.detectEnemyMissile(enemyMissiles, missiles);

            // collision for enemy missiles and player 
            collision.player_EnemyMissileCollision(enemyMissiles, userPlayer.getPlayer(), userPlayer);
        }
      
        // boss animation

        boss.bossAnimator(window,level.getSpawnBoss());

        //boss movement
        boss.bossMovement(window, level.getSpawnBoss());
        
        
        //check player hp
        userPlayer.hpChecker(window);

        lifeCountText.setString(std::to_string(userPlayer.getPlayerHp()));

        level.levelChecker(collision.getKillCount(), enemy);

        window.clear();
     

        //draw animations

        window.draw(backGround);
        if (level.getSpawnBoss() == true) {
            boss.drawBoss(window);
        }
        

        enemy.drawEnemy(window, enemies);

        userPlayer.drawPlayer(window);

        missile.drawMissiles(window,missiles);

        collision.drawExplosion(window, clock);


        window.draw(killCountText);
        window.draw(killCountLabel);
        window.draw(lifeCountLabel);
        window.draw(lifeCountText);


        if (level.getShootFlag() == true) {
            enemyMissile.drawEnemyMissile(window, enemyMissiles);
        }

        window.display();
    }

}

