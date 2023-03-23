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

using namespace sf;



int main()
{
    RenderWindow window(VideoMode(700, 500), "Space Impact");

    window.setFramerateLimit(60);

    int playerAnimation = 0;
    int enemySpawnTimer = 0;    
    int enemySpawnDuration = 100;
    int enemyImageCount = 0;
    int collisionImageCount = 0;
    int missileImageCount = 0;
    Collision collision("textures/explode.png");
   
   
    std::vector <Sprite> enemies;
    std::vector <Sprite> missiles;

    Texture bgTexture;
    Sprite backGround;

    if (!bgTexture.loadFromFile("textures/background.png"))
        throw  "can't load png";
   
    backGround.setTexture(bgTexture);
    backGround.setScale(1.1f, 1.1f);

    //player
    Player userPlayer("textures/Ligher.png");

    
   ;    //missile
    Missile missile("textures/06.png" );


    //enemy
    Enemy enemy("textures/purpleShip.png");

    
   
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

        userPlayer.updateAnimation(playerAnimation);

       

        if (clock.getElapsedTime().asSeconds() > .1f) {
             enemyImageCount++;
            playerAnimation ++;
            collisionImageCount++;
            clock.restart();
           
        }
         
      
       
        if (playerAnimation == 4) {
        
            playerAnimation = 0;
        }
           

        if (enemyImageCount == 4) {

            enemyImageCount = 0;
        }

        if (collisionImageCount == 8) {

            collisionImageCount = 0;
        }

        


            
        //trigger
       missile.shootMissiles(missiles);
        
         //missile/projectile projection

        missile.missilesMovement(window, missiles);

        //enemy spawn 

        if (enemySpawnTimer < enemySpawnDuration)
        enemySpawnTimer++;

        if (enemySpawnTimer >= enemySpawnDuration) {
            enemy.enemySpawn(window,enemies);
            enemySpawnTimer = 0;
        }
        
        //enemy movement
        enemy.enemyMovement(window,enemies, enemyImageCount);

        //detection for collision of projectiles and enemies
       
        collision.enemy_missileCollision(missiles, enemies,collisionImageCount);
        //collision for enemies and player
        collision.enemy_playerCollision(enemies, userPlayer.getPlayer());


        window.clear();
     

        //drawinga imong nawng

        window.draw(backGround);

        enemy.drawEnemy(window, enemies);

        userPlayer.drawPlayer(window);

        missile.drawMissiles(window,missiles);

        window.display();
    }

}

