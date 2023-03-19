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
   
    Collision collision;
   
   
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
    Missile missile("textures/missile.png" );


    //enemy
    Enemy enemy("textures/enemy2.png");

    
   
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
        
        missile.setCenterPosition(userPlayer.getPlayer().getPosition().x + 20, userPlayer.getPlayer().getPosition().y + 20);

        userPlayer.updateAnimation(playerAnimation);
       
       

        if (clock.getElapsedTime().asSeconds() > .1f) {

            playerAnimation ++;
            clock.restart();
           
        }
         
      
       
        if (playerAnimation == 4) {
        
            playerAnimation = 0;
        }
           
        

        std::cout << playerAnimation;
            
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
        enemy.enemyMovement(window,enemies);

        //detection for collision of projectiles and enemies
       
        collision.enemy_missileCollision(missiles, enemies);
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

