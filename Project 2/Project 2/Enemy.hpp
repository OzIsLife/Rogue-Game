//
//  Enemy.hpp
//  Project 2
//
//  Created by Khai on 2/17/19.
//  Copyright © 2019 Khai. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <utility>
#include <vector>

class Enemy {
    public:
        Enemy();
        virtual ~Enemy();
        
    protected:
        //Enemy image and coordinate for the screen
        SDL_Surface *enemySprite;
        std::vector<SDL_Rect> enemyPosition;
};

#endif /* Enemy_hpp */
