//
//  Player.hpp
//  Project 2
//
//  Created by Khai on 2/17/19.
//  Copyright © 2019 Khai. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Player {
    public:
        Player();
        virtual ~Player();
    
    protected:
        //Player image and coordinate for the screen
        SDL_Surface *playerSprite;
        SDL_Rect playerPosition;
        
        //Current direction for shooting
        SDL_Keycode currentDirection;
    
        //How many arrow does player have
        int numArrow;
};

#endif /* Player_hpp */
