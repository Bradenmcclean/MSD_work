//
//  EnemiesClass.cpp
//  Gal
//
//  Created by Kristina Colton on 9/22/20.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

// Not going to lie. No idea what this does but tutorial says I need this.

class Enemy
{
public:
    bool isShot;
    sf::Sprite pSprite;
    
    /* Default Constructor */
    Enemy() {
        
    }
    
    /* Constructor */
    // Takes an imgPath to use as sprite texture, and an x and y coordinate position to place sprite
    Enemy(string imgPath, float x, float y) {
        // Look up texture constructor
        pTexture = new sf::Texture;
        
        // If image for texture not found, print an error
        if (!pTexture->loadFromFile(imgPath)) {
            cout << "Error! Cannot find image." << endl;
        }
        // Set the texture for the sprite
        pSprite.setTexture(*pTexture);
        
        // Set the size of the sprite
        pSprite.setScale(sf::Vector2f(0.1,0.1));
        
        // Set the position of the sprite
        pSprite.setPosition(x, y);
        isShot=false;
    }
    //For Shooting
       bool randomGeneratorForEnemies()
        {
            int rand= std::rand()%2000;
            if (rand==1)
            {
                return true;
            }
            return false;
        }
    /* Draw sprite to a given window reference*/
    void drawEnemy(sf::RenderWindow &window)
    {
        window.draw(pSprite);
    }
    
    sf::Sprite getSprite() {
        return pSprite;
    }
    
private:
    
    sf::Texture* pTexture;
    
};


class EnemySquad {
public:
    
    vector<Enemy> myEnemySquad;
    float negVelocity = -0.6;
    float posVelocity = 0.6;
    // Initialize velocity in positive direction
    float velocity = posVelocity;
    
    
    /* Default Constructor */
    EnemySquad() {
        
    }
    
    /* Constructor */
    EnemySquad(vector<Enemy> enemies) {
        myEnemySquad = enemies;
    }
   
    
    void drawEnemySquad(sf::RenderWindow &window)
    {
        for (Enemy e : myEnemySquad)
        {
            if (e.isShot==false)
            {
            e.drawEnemy(window);
            }
        }
    }
    
    Enemy operator[](int index) {
        return myEnemySquad[index];
    }
    
    void checkBoundandMove(float x)
    {
        // Check that left-most enemy is in bounds
        //the 25 is to keep it in the window you see
        if(myEnemySquad[0].pSprite.getPosition().x<25)
        {
            // Move in positive direction
            velocity = posVelocity;
        }
        //the minus is to keep it in the window you see
        else if (myEnemySquad[myEnemySquad.size() - 1].pSprite.getPosition().x>x-125)
        {
            velocity = negVelocity;
            for (int i = 0; i < myEnemySquad.size(); i++) {
                myEnemySquad[i].pSprite.move(0, 20);
            }
        }
        for (int i = 0; i < myEnemySquad.size(); i++) {
            myEnemySquad[i].pSprite.move(velocity, 0);
        }
        
    }
    
private:
    
};



