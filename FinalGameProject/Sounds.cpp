//
//  Sounds.cpp
//  Gal
//
//  Created by Braden McClean on 9/24/20.
//
#include <iostream>
#include <stdio.h>
#include <SFML/Audio.hpp>
using namespace std;
struct soundEffect
{
    
    soundEffect()
    {
        if (!buffer.loadFromFile("pew.wav"))
        {
            cout<<"SOUND BROKE GO FIX IT"<<endl;
        }
        
        sound.setBuffer(buffer);

    }
    sf::SoundBuffer buffer;
    sf::Sound sound;
    
};
struct Music
{
    
    
};
