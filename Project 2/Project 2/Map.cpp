//
//  Map.cpp
//  Project 2
//
//  Created by Khai on 2/17/19.
//  Copyright © 2019 Khai. All rights reserved.
//

#include "Map.hpp"

Map::Map() :
    arrowSprite(SDL_LoadBMP("../Project 2/Sprite/Arrow.bmp")),
    wallSprite(SDL_LoadBMP("../Project 2/Sprite/Wall.bmp")),
    floorSprite(SDL_LoadBMP("../Project 2/Sprite/Floor.bmp")),
    chestSprite(SDL_LoadBMP("../Project 2/Sprite/Chest.bmp"))
{
    SDL_SetColorKey(arrowSprite, SDL_TRUE, SDL_MapRGB(arrowSprite->format, 255, 255, 255));
    SDL_SetColorKey(chestSprite, SDL_TRUE, SDL_MapRGB(chestSprite->format, 255, 255, 255));
}

//Freeing the image (No memory leak)
Map::~Map()
{
    SDL_FreeSurface(arrowSprite);
    SDL_FreeSurface(wallSprite);
    SDL_FreeSurface(floorSprite);
    SDL_FreeSurface(chestSprite);
}

//Getting the text file to the vector
void Map::mapText()
{
    std::ifstream mapWall("Level One.txt");
    std::string line;
    
    if(mapWall.is_open())
    {
        while(getline(mapWall, line))
        {
            mapMaze.push_back(line);
            //This for loop will check each character, if it a wall, player, floor, etc.
            for(int i = 0; i < 20; ++i)
            {
                if((mapMaze.back())[i] == 'X')
                    wallPosition.push_back({i * 24, static_cast<int>(mapMaze.size() - 1) * 24, 0, 0});
                else
                {
                    if((mapMaze.back())[i] == 'P')
                        Player::playerPosition = {i * 24, static_cast<int>(mapMaze.size() - 1) * 24, 0, 0};
                    else if((mapMaze.back())[i] == 'E')
                        Enemy::enemyPosition.push_back({i * 24, static_cast<int>(mapMaze.size() - 1) * 24, 0, 0});
                    else if((mapMaze.back())[i] == 'A')
                        arrowPosition.push_back({i * 24, static_cast<int>(mapMaze.size() - 1) * 24, 0, 0});
                    else if((mapMaze.back())[i] == 'C')
                        chestPostion = {i * 24, static_cast<int>(mapMaze.size() - 1) * 24, 0, 0};
                    
                    floorPosition.push_back({i * 24, static_cast<int>(mapMaze.size() - 1) * 24, 0, 0});
                }
            }
        }
        mapWall.close();
    }
}

//Move player
void Map::checkPlayerMove(SDL_Keycode kC)
{
    int yPos = Player::playerPosition.y / 24, xPos = Player::playerPosition.x / 24;
    
    switch(kC)
    {
        case SDLK_w:
            if(checkTile(yPos - 1, xPos))
            {
                mapMaze[yPos][xPos] = ' ';
                mapMaze[yPos - 1][xPos] = 'P';
                Player::playerPosition.y -= 24; //Move Sprite up
                Player::currentDirection = SDLK_w; //Store the current direction so it can shoot in the same direction
            }
            break;
        case SDLK_a:
            if(checkTile(yPos, xPos - 1))
            {
                mapMaze[yPos][xPos] = ' ';
                mapMaze[yPos][xPos - 1] = 'P';
                Player::playerPosition.x -= 24; //Move Sprite left
                Player::currentDirection = SDLK_a; //Store the current direction so it can shoot in the same direction
                
            }
            break;
        case SDLK_s:
            if(checkTile(yPos + 1, xPos))
            {
                mapMaze[yPos][xPos] = ' ';
                mapMaze[yPos + 1][xPos] = 'P';
                Player::playerPosition.y += 24; //Move Sprite down
                Player::currentDirection = SDLK_s; //Store the current direction so it can shoot in the same direction
            }
            break;
        case SDLK_d:
            if(checkTile(yPos, xPos + 1))
            {
                mapMaze[yPos][xPos] = ' ';
                mapMaze[yPos][xPos + 1] = 'P';
                Player::playerPosition.x += 24; //Move Sprite right
                Player::currentDirection = SDLK_d; //Store the current direction so it can shoot in the same direction
            }
            break;
        case SDLK_SPACE:
            if(Player::numArrow)
            {
                switch(Player::currentDirection)
                {
                    case SDLK_w:
                        while(mapMaze[yPos - 1][xPos] == ' ' || mapMaze[yPos - 1][xPos] == 'A') //Until it not a wall or enemy, keep doing
                            --yPos;
                        --yPos;
                        break;
                        
                    case SDLK_a:
                        while(mapMaze[yPos][xPos - 1] == ' ' || mapMaze[yPos][xPos - 1] == 'A')
                            --xPos;
                        --xPos;
                        break;
                        
                    case SDLK_s:
                        while(mapMaze[yPos + 1][xPos] == ' ' || mapMaze[yPos + 1][xPos] == 'A')
                            ++yPos;
                        ++yPos;
                        break;
                        
                    case SDLK_d:
                        while(mapMaze[yPos][xPos + 1] == ' ' || mapMaze[yPos][xPos + 1] == 'A')
                            ++xPos;
                        ++xPos;
                        break;
                }
                
                --(Player::numArrow); //Decrease the number of arrows
                if(mapMaze[yPos][xPos] == 'E') //If the arrow hit the enemy. Delete that specific enemy
                    for(int i = 0; i < Enemy::enemyPosition.size(); ++i)
                        if(yPos * 24 == Enemy::enemyPosition[i].y && xPos * 24 == Enemy::enemyPosition[i].x)
                        {
                            mapMaze[yPos][xPos] = ' ';
                            Enemy::enemyPosition.erase(Enemy::enemyPosition.begin() + i);
                        }
            }
            break;
    }
}

//Check the tile to see if it the enemy, wall, arrow or chest
bool Map::checkTile(int y, int x)
{
    if(mapMaze[y][x] == 'X') //If it is a wall dont move
        return false;
    else if(mapMaze[y][x] == 'C' || mapMaze[y][x] == 'E') //If it is a enemy or chest. Stop the game
        isRuuning = false;
    else if(mapMaze[y][x] == 'A')
    {
        ++(Player::numArrow);
        std::cout << "Arrow: " << numArrow << std::endl;
        for(unsigned int i = 0; i < arrowPosition.size(); ++i)
            if(y * 24 == arrowPosition[i].y && x * 24 == arrowPosition[i].x)
                arrowPosition.erase(arrowPosition.begin() + i);
    }
    
    return true;
}

//Short path
/*
 For you sake Professor Cecotti or anyone reading this function. Don't. Just know it work.
 If you do, you in the world of pain. Even I don'2t wanna read this code.
 Didn't have time to make a better version of this function.
 This the best way I can do with limited time.
 You've be warn!
 */
void Map::BFS(int i)
{
    //Getting the coordinate
    int yPos = Enemy::enemyPosition[i].y / 24, xPos = Enemy::enemyPosition[i].x / 24;
    
    //Initialize the array to false
    bool visit[20][20];
    for(int i = 0; i < 20; ++i)
        for(int j = 0; j < 20; ++j)
            visit[i][j] = false;
    
    //For enemy to go different path
    std::queue<std::pair<int, int> > enemyPos;
    enemyPos.push(std::make_pair(yPos, xPos));
    
    //Get all the path. It will make a pair of the coordinate and the index of the the previous step
    std::vector<std::pair<std::pair<int, int>, int> > allPath;
    allPath.push_back(std::make_pair(std::make_pair(yPos, xPos), INT_MAX));
    
    int prevPath = 0;
    
    while(!enemyPos.empty())
    {
        std::pair<int, int> curr = enemyPos.front();
        visit[curr.first][curr.second] = true;
        enemyPos.pop();
        
        //up
        if(mapMaze[curr.first - 1][curr.second] != 'X' && !visit[curr.first - 1][curr.second])
        {
            visit[curr.first - 1][curr.second] = true;
            enemyPos.push(std::make_pair(curr.first - 1, curr.second));
            allPath.push_back(std::make_pair(std::make_pair(curr.first - 1, curr.second), prevPath));
            if(curr.first - 1 == Player::playerPosition.y / 24 && curr.second == Player::playerPosition.x / 24)
                break;
        }
        
        //left
        if(mapMaze[curr.first][curr.second - 1] != 'X' && !visit[curr.first][curr.second - 1])
        {
            visit[curr.first][curr.second - 1] = true;
            enemyPos.push(std::make_pair(curr.first, curr.second - 1));
            allPath.push_back(std::make_pair(std::make_pair(curr.first, curr.second - 1), prevPath));
            if(curr.first == Player::playerPosition.y / 24 && curr.second - 1 == Player::playerPosition.x / 24)
                break;
        }
        
        //down
        if(mapMaze[curr.first + 1][curr.second] != 'X' && !visit[curr.first + 1][curr.second])
        {
            visit[curr.first + 1][curr.second] = true;
            enemyPos.push(std::make_pair(curr.first + 1, curr.second));
            allPath.push_back(std::make_pair(std::make_pair(curr.first + 1, curr.second), prevPath));
            if(curr.first + 1 == Player::playerPosition.y / 24  && curr.second == Player::playerPosition.x / 24 )
                break;
        }
        
        //right
        if(mapMaze[curr.first][curr.second + 1] != 'X' && !visit[curr.first][curr.second + 1])
        {
            visit[curr.first][curr.second + 1] = true;
            enemyPos.push(std::make_pair(curr.first, curr.second + 1));
            allPath.push_back(std::make_pair(std::make_pair(curr.first, curr.second + 1), prevPath));
            if(curr.first == Player::playerPosition.y / 24  && curr.second + 1 == Player::playerPosition.x / 24 )
                break;
        }
        ++prevPath;
    }
    
    //Will get the final path
    std::stack<std::pair<int, int> > finalPath;
    finalPath.push(allPath.back().first);
    int coor = allPath.back().second;
    
    while(coor != INT_MAX)
    {
        finalPath.push(allPath[coor].first);
        coor = allPath[coor].second;
    }
    
    finalPath.pop();
    
    //Will check if it space
    if(mapMaze[finalPath.top().first][finalPath.top().second] == ' ')
    {
        mapMaze[yPos][xPos] = ' ';
        enemyPosition[i] = {finalPath.top().second * 24, finalPath.top().first * 24, 0, 0};
        mapMaze[enemyPosition[i].y / 24][enemyPosition[i].x / 24] = 'E';
    }
    else if(mapMaze[finalPath.top().first][finalPath.top().second] == 'P') //If it the player. Game Over!
        isRuuning = false;
}

//Reseting everything
void Map::resetMap()
{
    mapMaze.clear();
    arrowPosition.clear();
    enemyPosition.clear();
    floorPosition.clear();
    wallPosition.clear();
    mapText();
    Player::numArrow = 1;
}
