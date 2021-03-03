//
//  Main.cpp
//  Gal
//
//  Created by Braden McClean on 9/22/20.
//
#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include"GalacticaClass.cpp"
#include <SFML/Audio.hpp>
#include "Sounds.cpp"
int main()
{
    
    // create the window
    float windowX=2800;
    float windowY=3000;
    bool endgame=false;
    while (endgame==false)
    {

    galacticaGame game=galacticaGame("background.png","Pacifico.ttf",windowX,windowY);
    sf::RenderWindow windowstarts(sf::VideoMode(windowX, windowY), "Start Window");
    sf::Music intromusic;
            if (!intromusic.openFromFile("underground-town.ogg"))
            {
               return -1; // error
            }
           intromusic.play();
           intromusic.setVolume(60);
        while (windowstarts.isOpen())
        {
           
            
            sf::Event event;
            while (windowstarts.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    windowstarts.close();
                }
                if (event.type == sf::Event::KeyPressed)
                {

                      
                    if (event.key.code==sf::Keyboard::D)
                    {
                        windowstarts.close();
                    }
                }
                
                
            }
             windowstarts.draw(game.pSprite);
            windowstarts.draw(game.text);
            windowstarts.draw(game.starttxt);
            windowstarts.display();
        }
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "My window");
    intromusic.stop();
    sf::Music music;
    if (!music.openFromFile("unprepared.ogg"))
        return -1; // error
    music.play();
    music.setVolume(60);
    //create my space ship boi
    soundEffect pew;
    pew.sound.setVolume(20);
    spaceShip player=spaceShip("GalagaSpaceShip.png",1450,1400);
    vector<Projectiles> spaceShipMissles;
    vector<Projectiles> enemyLasers;
    // Create a vector of enemies
    vector<Enemy> enemies;
    float x = 500;
    float y = 50;
    float z = 500;
    float k = 500;
    for (int i = 1; i < 28; i++)
    {
        Enemy myEnemy;
        if (i<10)
        {
        myEnemy = Enemy("spaceinvader3.png", x, y);
             x += 200;
        }
        else if (i<19)
        {
            myEnemy = Enemy("spaceinvader2.png", z, y+150);
            z+=200;
        }
        else
        {
            myEnemy = Enemy("spaceinvader.png", k, y+300);
            k+=200;
        }
        enemies.push_back(myEnemy);
       
    }
  
    
    // create enemy squad instance using vector of enemies
    EnemySquad myEnemySquad(enemies);
    
    // run the program as long as the window is open
    while (window.isOpen())
       {
           
           // check all the window's events that were triggered since the last iteration of the loop
           sf::Event event;
           while (window.pollEvent(event))
           {
               // "close requested" event: we close the window
               if (event.type == sf::Event::Closed)
               {
                   window.close();
               }
               if (event.type == sf::Event::KeyPressed)
                {

                      
                    if (event.key.code==sf::Keyboard::D)
                    {

                        //this if statment sees if the key is pressed and
                        //keeps the speed to a max velocity
                        if (event.key.code==sf::Keyboard::D&& player.velocity<player.maxPostiveVelocity)
                        {
                            //the velocity and the accleration are in
                            //the class
                            player.velocity+=player.postiveAccleration;
                            player.checkBoundandMove(windowX);
                        }
                    }
                    else if (event.key.code==sf::Keyboard::A)
                    {
                        
                        //flip all the signs
                        if (event.key.code==sf::Keyboard::A&& player.velocity>player.maxNegativeVelocity)
                        {
                            //the velocity and the accleration are in
                            //the class
                            player.velocity+=player.negativeAccleration;
                             player.checkBoundandMove(windowX);
                        }
                        else
                        {
                            //keeps the thing moveing after reaching maxVelocity
                             player.checkBoundandMove(windowX);
                        }
                    }

                    else if (event.key.code==sf::Keyboard::W)
                    {
                     Projectiles myProjectiles =Projectiles("spaceShipProjectile.png",(player.pSprite.getPosition().x+42),(player.pSprite.getPosition().y-35));
                     spaceShipMissles.push_back(myProjectiles);
                        pew.sound.play();
                    }
                   
                }
              else
              {
                  player.velocityToZero();
              }
           
                
           }
          
            // clear the window with black color
            window.clear(sf::Color::Black);
            // Draw the enemy squad in the window
            myEnemySquad.drawEnemySquad(window);
            player.checkBoundandMove(windowX);
            // Move the enemy squad
            myEnemySquad.checkBoundandMove(windowX);
            //Shooting for the enemies with a random generator
            Projectiles enemyShoot;
            game.enemyShooter(myEnemySquad, enemyLasers);
            //Draws the spaceShip
            player.drawSpaceShip(window);
           
        vector<int> checkingProjectiles={};
        for (int i=0;i<spaceShipMissles.size();i++)
        {
            bool flag=false;
           spaceShipMissles[i].drawProjectile(window);
            flag=spaceShipMissles[i].checkBoundandMove(windowX,myEnemySquad.myEnemySquad);
            if (flag==true)
            {
            checkingProjectiles.push_back(i);
            }
        }
           for (int i=0;i<checkingProjectiles.size();i++)
           {
               //erase the missles when they hit something that destories it
               //we had a problem that when you delete in your ShipMisssles vector
               //you would shift all the postions right
               //causing you checking missles to be one off after the first itteration
               //so -i big brain time
               spaceShipMissles.erase(spaceShipMissles.begin()+(checkingProjectiles[i]-i));
           }
           
           //resetingPROJECTILES FOR LASERS
       checkingProjectiles={};
        for (int i=0;i<enemyLasers.size();i++)
        {
            bool flag=false;
            flag=enemyLasers[i].checkBoundandMoveLaser(windowY,player);
            enemyLasers[i].drawProjectile(window);
            if (flag==true)
            {
            checkingProjectiles.push_back(i);
            }
        }
        for (int i=0;i<checkingProjectiles.size();i++)
        {
            enemyLasers.erase(enemyLasers.begin()+(checkingProjectiles[i]-i));
        }

                       
       // end the current frame
       window.display();
           if (player.isShot)
           {
               game.didYouWinSon=false;
               window.close();
           }
           if (game.winChecker(myEnemySquad.myEnemySquad))
           {
               game.didYouWinSon=true;
               window.close();
           }
       }
    
  sf::RenderWindow windowend(sf::VideoMode(windowX, windowY), "End window");
    galacticaGame end ("lose.png","win.png",windowX,windowY);
    music.stop();
    while (windowend.isOpen())
          {
             
              
              sf::Event event;
              while (windowend.pollEvent(event))
              {
                  if (event.type == sf::Event::Closed)
                  {
                      windowend.close();
                  }
                  if (event.type == sf::Event::KeyPressed)
                  {

                        
                      if (event.key.code==sf::Keyboard::D)
                      {
                          windowend.close();
                      }
                      if (event.key.code==sf::Keyboard::A)
                       {
                           endgame=true;
                           windowend.close();
                       }
                  }
                  
                  
              }
              if (game.didYouWinSon)
              {
                  game.text.setString("YOU WON!\n Press D to Start Again \n Or Press A to End the Game");
                  game.text.setPosition(1500, 600);
                  game.text.setCharacterSize(80);
                  game.text.setStyle( sf::Text::Regular);
                 
                windowend.draw(end.winSprite);
                 windowend.draw(game.text);
               
              }
              else
              {
                  game.text.setString("YOU SUCK!\n Press D to Start Again \n Or Press A to End the Game");
                  game.text.setPosition(1800, 600);
                  game.text.setCharacterSize(80);
                  game.text.setStyle( sf::Text::Regular);
                  windowend.draw(end.pSprite);
                  windowend.draw(game.text);
              }
              windowend.display();
          }
    }
    return 0;
}
