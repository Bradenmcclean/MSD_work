//
//  Projectiles.cpp
//  Gal
//
//  Created by Braden McClean on 9/23/20.
//

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include"EnemiesClass.cpp"
#include "SpaceShipPlayer.cpp"
using namespace std;
class Projectiles
{public:
    //default constructor
    Projectiles() {
        
    }
    
    
    //USE RIGHT IMGPATH FOR ENEMY AND PLAYER

    Projectiles(string imgPath, float x, float y)
    {
          
        // Look up texture constructor
        pTexture = new sf::Texture;
        
        // If image for texture not found, print an error
        
        // If image for texture not found, print an error
            if (!pTexture->loadFromFile(imgPath)) {
                cout << "Error! Cannot find image Projectile in "<< imgPath<<"." << endl;
            }
           // Set the texture for the sprite
           pSprite.setTexture(*pTexture);
           
           // Set the size of the sprite had to make differnt sizes
            if (imgPath=="enemyProjectile.png")
            {
           pSprite.setScale(sf::Vector2f(0.15,0.15));
            }
            else
            {
           pSprite.setScale(sf::Vector2f(0.05,0.05));
            }
           // Set the position of the sprite
           pSprite.setPosition(x, y);
           
       }
    
   
    bool checkBoundandMove(float x,vector<Enemy>& group)
    {
        bool flag = false;
        //if the sprite hits the top of the screen flag false
        if(pSprite.getPosition().y<0)
        {
            //moving 0 didnt work so I FORCED IT TO BE THERE
            flag=true;
            return flag;
        }
        for (int i=0;i<group.size();i++)
        {
            if(pSprite.getGlobalBounds().intersects(group[i].getSprite().getGlobalBounds())&&group[i].isShot==false)
            {
                //all this mess was testing the bounds of the projectile
                //and the enemy
//                cout<<pSprite.getGlobalBounds().top<<" top Projectile"<<endl;
//                 cout<<pSprite.getGlobalBounds().left<<"left,"<<(pSprite.getGlobalBounds().width+pSprite.getGlobalBounds().left)<<" right Projectile"<<endl;
//                cout<<(group[i].getSprite().getGlobalBounds().top+group[i].getSprite().getGlobalBounds().height)<<" bottom Enemy"<<endl;
//                cout<<group[i].getSprite().getGlobalBounds().left<<"left, "<<(group[i].getSprite().getGlobalBounds().left+group[i].getSprite().getGlobalBounds().width)<<"right Enemy"<<endl;
//                cout<<"Hit"<<endl;
                
                group[i].isShot=true;
                flag=true;
                return flag;
            }
        }
        pSprite.move(0, -2);
        return flag;
    }
    
    sf::Texture* pTexture;
    sf::Sprite pSprite;
    
    void drawProjectile(sf::RenderWindow &window)
       {
           window.draw(pSprite);
       }
    
  bool checkBoundandMoveLaser(float y,spaceShip& player)
     {
         bool flag = false;
         //if the sprite hits the bottom of the screen flag false
         if(pSprite.getPosition().y>y)
         {
             flag=true;
             return flag;
         }
         if(pSprite.getGlobalBounds().intersects(player.pSprite.getGlobalBounds())&& player.isShot==false)
             {
                 player.isShot=true;
                 flag=true;
                 return flag;
             }
         pSprite.move(0, 1);
         return flag;
     }
    
   
};
