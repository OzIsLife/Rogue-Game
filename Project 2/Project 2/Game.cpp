//
//  Game.cpp
//  Project 2
//
//  Created by Khai on 2/17/19.
//  Copyright © 2019 Khai. All rights reserved.
//

#include "Game.hpp"

Game::Game() :
    gameWindow(NULL), gameScreen(NULL),
    gameMenu(SDL_LoadBMP("../Project 2/Sprite/Menu.bmp")),
    screenWidth(480), screenHeight(480), isMenuRunning(true)
{ }

Game::~Game()
{
    SDL_DestroyWindow(gameWindow);
    SDL_FreeSurface(gameScreen);
    SDL_Quit();
}

//Initialize window and screen
void Game::gameInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Did not initialize correctly. Error: %s", SDL_GetError());
        Map::isRuuning = false;
    }
    else
    {
        gameWindow = SDL_CreateWindow("Our Life is Dead", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
        if(!gameWindow)
        {
            printf("Window did not initialize correctly. Error: %s", SDL_GetError());
            Map::isRuuning = false;
        }
        else
        {
            gameScreen = SDL_GetWindowSurface(gameWindow);
            if(!gameScreen)
            {
                printf("Render did not initialize correctly. Error: %s", SDL_GetError());
                Map::isRuuning = false;
            }
            mapText();
        }
    }
}

//Check events
void Game::gameEvent()
{
    while(SDL_PollEvent(&gameEvents))
    {
        switch(gameEvents.type)
        {
            case SDL_QUIT:
                Map::isRuuning = false;
                break;
            case SDL_KEYDOWN:
                checkPlayerMove(gameEvents.key.keysym.sym);
                if(Map::isRuuning)
                {
                    for(int i = 0; i < getEnemySize(); ++i)
                        BFS(i);
                }
                break;
        }
    }
}

//Display game on screen
void Game::gameOnDisplay()
{
    SDL_FillRect(gameScreen, NULL, 0x000000);
    
    for(unsigned int i = 0; i < Map::wallPosition.size(); ++i)
        SDL_BlitSurface(Map::wallSprite, NULL, gameScreen, &wallPosition[i]);
    
    for(unsigned int i = 0; i < Map::floorPosition.size(); ++i)
        SDL_BlitSurface(Map::floorSprite, NULL, gameScreen, &floorPosition[i]);
    
    for(unsigned int i = 0; i < Map::arrowPosition.size(); ++i)
        SDL_BlitSurface(Map::arrowSprite, NULL, gameScreen, &arrowPosition[i]);
    
    SDL_BlitSurface(Map::chestSprite, NULL, gameScreen, &chestPostion);
    
    for(unsigned int i = 0; i < getEnemySize(); ++i)
        SDL_BlitSurface(getEnemySprite(), NULL, gameScreen, getEnemyPosition(i));
    
    SDL_BlitSurface(getPlayerSprite(), NULL, gameScreen, getPlayerPosition());
    
    SDL_UpdateWindowSurface(gameWindow);
}

//Display menu on screen
void Game::gameOffDiplay()
{
    SDL_FillRect(gameScreen, NULL, 0x000000);
    SDL_BlitSurface(gameMenu, NULL, gameScreen, NULL);
    SDL_UpdateWindowSurface(gameWindow);
}


