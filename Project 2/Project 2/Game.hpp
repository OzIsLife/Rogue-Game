//
//  Game.hpp
//  Project 2
//
//  Created by Khai on 2/17/19.
//  Copyright © 2019 Khai. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Map.hpp"

#include <SDL2/SDL.h>
#include <stdio.h>

class Game : Map {
    public:
        Game();
        virtual ~Game();
    
        //Events and Display
        void gameInit();
        void gameEvent();
        void gameOnDisplay();
        void gameOffDiplay();
    
        //Set and Get for the menu (if the menu is running or not)
        bool getGameMenuRuning() { return isMenuRunning; }
        void setGameMenuRunning(bool iMR) { isMenuRunning = iMR; }
    
        //Set and Get for the game(if the game is running or not)
        bool getGameIsRunning() { return Map::isRuuning; }
        void setGameIsRunning(bool iR) { Map::isRuuning = iR; }
    
        //How many enemy are left
        int  gameContainEnemy() { return Map::getEnemySize(); }
    
        //Reseting everything
        void gameReset() { Map::resetMap(); }
    
    private:
        //Create the window
        SDL_Window *gameWindow;
        //Create the screen
        SDL_Surface *gameScreen;
        //Create events (move and shoot)
        SDL_Event gameEvents;
        //Create the screen for the menu
        SDL_Surface *gameMenu;
    
        bool isMenuRunning;
        int screenWidth;
        int screenHeight;
};

#endif /* Game_hpp */
