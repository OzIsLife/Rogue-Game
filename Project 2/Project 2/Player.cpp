//
//  Player.cpp
//  Project 2
//
//  Created by Khai on 2/17/19.
//  Copyright © 2019 Khai. All rights reserved.
//

#include "Player.hpp"

Player::Player() :
    playerSprite(SDL_LoadBMP("../Project 2/Sprite/Character/Player.bmp")), currentDirection(SDLK_s), numArrow(1)
{
    SDL_SetColorKey(playerSprite, SDL_TRUE, SDL_MapRGB(playerSprite->format, 255, 255, 255));
}

Player::~Player() { SDL_FreeSurface(playerSprite); }

