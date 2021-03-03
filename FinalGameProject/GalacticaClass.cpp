#include <SFML/Graphics.hpp>
#include <iostream>
#include "Projectiles.cpp"
struct galacticaGame
{
    sf::Texture pTexture;
    sf::Sprite pSprite;
    sf::Font pFont;
    sf::Text text;
    sf::Text starttxt;
    sf::Texture winTexture;
    sf::Sprite winSprite;
    
    bool didYouWinSon;
    galacticaGame()
    {
        
    }
    galacticaGame(string imgPath, string fontPath, float x, float y)
       {
            // If image for texture not found, print an error
            if (!pTexture.loadFromFile(imgPath))
            {
                cout << "Error! Cannot find image SpaceShip." << endl;
            }
           
            // Set the texture for the sprite
            pSprite.setTexture(pTexture);
            
            // Set the size of the sprite
           pSprite.setScale(sf::Vector2f(1.5,1.5));
                   
           // Set the position of the sprite
           pSprite.setPosition(0,0);
           
           if (fontPath=="Pacifico.ttf")
            {
               if (!pFont.loadFromFile(fontPath))
               {
                   cout << "Error! Cannot find image SpaceShip." << endl;
               }
               text.setFont(pFont);
                // set the character size'
               text.setString("Galactica");
                text.setCharacterSize(200); // in pixels, not points!

                // set the color
                text.setFillColor(sf::Color::Green);

                // set the text style
                text.setStyle( sf::Text::Underlined);
               text.setPosition(1000, 400);
               
               starttxt.setFont(pFont);
               starttxt.setString("Press D to Start!");
              starttxt.setCharacterSize(100); // in pixels, not points!

              // set the color
              starttxt.setFillColor(sf::Color::Green);

              // set the text style
             starttxt.setPosition(990, 800);
           }
           else
           {
           if (!winTexture.loadFromFile(fontPath))
             {
                 cout << "Error! Cannot find image SpaceShip." << endl;
             }
   // Set the texture for the sprite
             winSprite.setTexture(winTexture);
             
             // Set the size of the sprite
               winSprite.setScale(sf::Vector2f(5,5));
                    
            // Set the position of the sprite
            winSprite.setPosition(0,300);
           }
        }
       
    bool winChecker(vector<Enemy> &goons)
    {
        for (int i=0;i<goons.size();i++)
        {
            if (goons[i].isShot==false)
                return false;
        }
        return true;
        
    }
    bool loseChecker(spaceShip &player)
    {
        return player.isShot;
    }
   void enemyShooter (EnemySquad &myEnemySquad,vector<Projectiles>&enemyLasers)
      {
      
      for (int i=0;i<myEnemySquad.myEnemySquad.size();i++)
                {
                    if (myEnemySquad[i].randomGeneratorForEnemies()&&myEnemySquad[i].isShot==false)
                    {
                        Projectiles enemyLaser =Projectiles("enemyProjectile.png",(myEnemySquad[i].pSprite.getPosition().x+42),(myEnemySquad[i].pSprite.getPosition().y+35));
                        enemyLasers.push_back(enemyLaser);
                    }
                }
      
      }
   

};
