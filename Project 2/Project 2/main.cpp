//
//  main.cpp
//  Project 2
//
//  Created by Khai on 2/17/19.
//  Copyright © 2019 Khai. All rights reserved.
//
#include "Game.hpp"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *args[]) {
    Game *game = new Game;
    SDL_Event e;
    
    //Initialize everything
    game->gameInit();
    
    while(game->getGameMenuRuning())
    {
        //Display the menu if not playing
        game->gameOffDiplay();
        
        //Will check if the user want to press P to play or O to quit
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym)
                {
                    case SDLK_p:
                        //Initialize the game
                        game->setGameIsRunning(true);
                        //Until the player is dead or kill all the enemy or got chest, keep checking for any events and display it on the screen
                        while(game->getGameIsRunning() && game->gameContainEnemy())
                        {
                            game->gameEvent();
                            game->gameOnDisplay();
                        }
                        //Reset game
                        game->gameReset();
                        break;
                    case SDLK_o:
                        //Destroying game and menu
                        game->setGameMenuRunning(false);
                        break;
                }
                    break;
                case SDL_QUIT:
                    //Destroying game and menu
                    game->setGameMenuRunning(false);
                    break;
            }
        }
    }
    
    delete game;
    return 0;
}
