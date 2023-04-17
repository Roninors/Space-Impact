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
#include "BossMissile.h"
#include "PowerUps.h"

using namespace sf;



int main()
{
    RenderWindow window(VideoMode(700, 500), "Space Impact");
    
    window.setFramerateLimit(60);
  
    //BACKGROUND

    Texture bgTexture;
    Sprite backGround;

    if (!bgTexture.loadFromFile("textures/background.png"))
        throw  "can't load png";

    backGround.setTexture(bgTexture);
    backGround.setScale(1.1f, 1.1f);


    //FONTS AND TEXTS

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
    lifeCountText.setPosition(Vector2f(320.f, 0.f));



    Text lifeCountLabel;
    lifeCountLabel.setFont(textFont);
    lifeCountLabel.setCharacterSize(20);
    lifeCountLabel.setString("Lives :");
    lifeCountLabel.setPosition(Vector2f(200.f, 0.f));

    Text bossLifeLabel;
    bossLifeLabel.setFont(textFont);
    bossLifeLabel.setCharacterSize(20);
    bossLifeLabel.setString("Boss Life :");
    bossLifeLabel.setPosition(Vector2f(400.f, 0.f));

    Text bossLifeCountText;
    bossLifeCountText.setFont(textFont);
    bossLifeCountText.setCharacterSize(20);
    bossLifeCountText.setPosition(Vector2f(580.f, 0.f));


    //VECTORS 
   
    std::vector <Sprite> enemies;
    std::vector <Sprite> missiles;
    std::vector <Sprite> enemyMissiles;
    std::vector <Sprite> bossMissiles;

    //Power up INSTANCE
    PowerUps powerUp("textures/heart.png","textures/explode.png", "textures/explode.png",window);

    //Collision INSTANCE
    Collision collision("textures/explode.png");

    //player INSTANCE
    Player userPlayer("textures/Ligher.png");

    
    //missile INSTANCE
    Missile missile("textures/06.png");


    //enemy INSTANCE
    Enemy enemy("textures/purpleShip.png");

    //Level INSTANCE
    Level level;
    
    //enemy missile INSTANCE
    EnemyMissile enemyMissile("textures/enemyProjectile.png");
    
   //timer INSTANCE
    Clock clock;

   //boss INSTANCE
    Boss boss("textures/boss1.png", window);

    //boss missile INSTANCE

    BossMissile bossMissile("textures/bossMissile.png");

    // Game loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }


        // UPDATE
        

        //player movement
        userPlayer.movePlayer(window);

        //position for center missile
        
        missile.setCenterPosition(userPlayer.getPlayer().getPosition().x +10, userPlayer.getPlayer().getPosition().y +10 );
   
        userPlayer.updateAnimation();

       
        //animation changer//counter

        if (clock.getElapsedTime().asSeconds() > .1f) {

            bossMissile.setBossMissileImg_Count();

            enemy.setEnemyImageCount();

            userPlayer.setPlayerAnimation();

            if (level.getBossShoot() == true)
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

        if (bossMissile.getBossMissileImg_Count() == 7) {

    
            bossMissile.resetBossMissileImg_Count();
        }
        


       //player trigger

       missile.shootMissiles(missiles);
        
        //player - missile/projectile trajection

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

        //enemy missile trajection and missile movement
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
        // only detects enemy missiles when missile spawn is happening

        if (level.getdetectionMissiles() == true) {

            // collision for enemy missiles and player missiles
            collision.detectEnemyMissile(enemyMissiles, missiles);

            // collision for enemy missiles and player 
            collision.player_EnemyMissileCollision(enemyMissiles, userPlayer.getPlayer(), userPlayer);
        }
      
        // boss animation
        if (level.getSpawnBoss() == true)
        boss.bossAnimator(window,level.getSpawnBoss());

        //boss movement
        if (level.getSpawnBoss() == true)
        boss.bossMovement(window, level.getSpawnBoss());
        
        //boss missile center
        if (level.getSpawnBoss() == true)
        bossMissile.setBossMissilePosition(boss.getBossSprite().getPosition().x, boss.getBossSprite().getPosition().y);

        //boss missile shooter
        if (level.getSpawnBoss() == true)
        bossMissile.bossShootMissiles(bossMissiles,boss.getBossImgCount());

        //boss missile movement/trajection
        bossMissile.bossMissilesMovement(window, bossMissiles);

        //boss missile detection
        // only detects boss missiles when missile spawn is happening

        if (level.getDetectionBossMissiles() == true) {
            
            //collision for boss and player missiles
            collision.detectBossMissiles(bossMissiles, missiles);
            
            //collision for boss missiles and player 
            collision.player_BossMissileCollision(bossMissiles, userPlayer.getPlayer(), userPlayer);


            collision.boss_PlayerMissileCollision(missiles, boss.getBossSprite(), boss);
        }



        //check player hp
        userPlayer.hpChecker(window);


        lifeCountText.setString(std::to_string(userPlayer.getPlayerHp()));

        level.levelChecker(collision.getKillCount(), enemy, boss, bossMissile, boss.getBossDeadDecider());


        //boss hp checker and life count
        boss.bossHpChecker();
        bossLifeCountText.setString(std::to_string(boss.getBossHp()));

        //boss level
        boss.bossLevelChecker();


        
       //powerup

      
        if (level.getSpawnHealth() == true) { 
          
            powerUp.powerUpMovement(window, level); }



        if (level.getSpawnHealth() == true) {
            
            collision.powerUpCollision(missiles, powerUp.getHealthSprite(), level);
        }
  
   

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

        //only draw boss missile when boss spawn is set to true
        if (level.getSpawnBoss() == true) {

            window.draw(bossLifeLabel);
            window.draw(bossLifeCountText);

            if (level.getBossShoot() == true) {

                bossMissile.drawBossMissile(window, bossMissiles);


            }
        }

 
   
        //labels and texts
        window.draw(killCountText);
        window.draw(killCountLabel);
        window.draw(lifeCountLabel);
        window.draw(lifeCountText);


        //only draws enemy missile when shoot flag for enemy shooting is set to true

        if (level.getShootFlag() == true) {
            enemyMissile.drawEnemyMissile(window, enemyMissiles);
        }

        if (level.getSpawnHealth() == true) {
           
            powerUp.drawHealthPowerUp(window);
        }
       

        window.display();
    }

}

