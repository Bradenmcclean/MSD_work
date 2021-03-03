//
//  SpaceShipPlayer.cpp
//  ALL_BUILD
//
//  Created by Braden McClean on 9/22/20.
//
#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>
using namespace std;
class spaceShip
{
    
//default constructor
    spaceShip() {
        
    }
    
    //Constructor
    // using the same logic as your enemy
    public:
    //have to make this public so you can move it
    bool isShot;
    sf::Sprite pSprite;
    
    //these  things are to make fluid movement
    float velocity;
    float maxPostiveVelocity=20;
    float maxNegativeVelocity=-20;
    float postiveAccleration=2;
    float negativeAccleration=-2;
    // setting to zero function so it looks cool
    void velocityToZero()
    {
        if (velocity>0)
        {
            //the co mputer itterates to fast for this to be bigger
            velocity*=.75;
        }
        if(velocity<0)
        {
            velocity*=.75;
        }
        
        
    }
    void checkBoundandMove(float x)
    {
        //the 25 is to keep it in the window you see
        if( pSprite.getPosition().x<25)
        {
            //moving 0 didnt work so I FORCED IT TO BE THERE
          pSprite.setPosition(25,1400);
        }
        //the minus is to keep it in the window you see
        else if (pSprite.getPosition().x>x-125)
        {
            pSprite.setPosition(x-125,1400);
        }
        pSprite.move(velocity, 0);
    }
    spaceShip(string imgPath, float x, float y) {
        // If image for texture not found, print an error
        if (!pTexture.loadFromFile(imgPath)) {
            cout << "Error! Cannot find image SpaceShip." << endl;
        }
        // Set the texture for the sprite
        pSprite.setTexture(pTexture);
        
        // Set the size of the sprite
        pSprite.setScale(sf::Vector2f(0.1,0.1));
        
        // Set the position of the sprite
        pSprite.setPosition(x, y);
        isShot=false;
    }
    
    /* Draw sprite to a given window reference*/
    void drawSpaceShip(sf::RenderWindow &window)
    {
        if(isShot==false)
        {
        window.draw(pSprite);
        }
    }
    
private:
    
    sf::Texture pTexture;
    
    
};

