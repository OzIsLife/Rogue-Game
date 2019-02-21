//
//  Enemy.cpp
//  Project 2
//
//  Created by Khai on 2/17/19.
//  Copyright © 2019 Khai. All rights reserved.
//

#include "Enemy.hpp"

Enemy::Enemy()
{
    enemySprite = SDL_LoadBMP("../Project 2/Sprite/Character/Enemy.bmp");
    SDL_SetColorKey(enemySprite, SDL_TRUE, SDL_MapRGB(enemySprite->format, 255, 255, 255));
    
}

Enemy::~Enemy() { SDL_FreeSurface(enemySprite); }
