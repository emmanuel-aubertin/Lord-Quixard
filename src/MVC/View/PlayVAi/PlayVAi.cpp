#include "PlayVAi.hpp"
#include <iostream>
#include <array>
#include <utility>
#include "../../../Player/PlayerHuman/PlayerHuman.hpp"
#include "../../../Player/AIPlayer/RandomAI/RandomAI.hpp"
#include "../MainMenu/MainMenu.hpp"
#include "../../../Tile.cpp"
#include "../View.hpp"
#include "../MageSMelee/MageSMelee.hpp"


PlayVAi::PlayVAi(SDL_Window *win) : MageSMelee(win)
{
    PlayerHuman *playerOne = new PlayerHuman("Thalira Mooncrest");
    RandomAI *playerTwo = new RandomAI("Lord Hazarde");
    engine = new GameEngine(*playerOne, *playerTwo);
}

PlayVAi::~PlayVAi() {
}

View *PlayVAi::handleClick(int x, int y)
{
    //std::cout << "cliked : " << x << ", " << y << std::endl;
    SDL_Point clickedPoint = {x, y};
    if (isPointInTile(clickedPoint, BACK_BTN))
    {
        return new MainMenu(window);
    }
    if(engine->isWinner()){
        return nullptr;
    }
    for (int i = 0; i < NUM_TILES; ++i)
    {
        if (isPointInTile(clickedPoint, TILE_COORDS[i]))
        {
            //std::cout << "Clicked on tile " << i << std::endl;
            if (indexCliked == -1)
            {
                indexCliked = i;
                break;
            }
            std::pair<int, int> coords = engine->getCoordsFromIndex(i);
            if (engine->move(indexCliked, coords.first, coords.second))
            {
                if(engine->isWinner()){
                    board = engine->getBoard();
                    indexCliked = -1;
                    break;
                }
                engine->printBoard();
                board = engine->getBoard();
                engine->makeIAmove();
                indexCliked = -1;
                break;
            }
            if (coords.first == 0 || coords.first == 4 || coords.second == 0 || coords.second == 4)
            {
                indexCliked = i; // New place to play
                break;
            }
            // Middle tile nothing todo
            break;
        }
    }
    return nullptr;
}

/*
// The following section is here to get all coords for a custom (not regular) grid.
int tileNum = 0;
int pointCounter = -1;
View *MageSMelee::handleClick(int x, int y)
{
    pointCounter++;
    if(pointCounter == 0){
        std::cout <<"{{" << x << ", "<< y  << "}, ";
        return nullptr;
    }
    if(pointCounter == 3){
        std::cout << "{" << x << ", "<< y  << "}}, " << std::endl;
        tileNum++;
        pointCounter =-1 ;
        return nullptr;
    }
    std::cout << "{" << x << ", "<< y  << "}, ";



    return nullptr;
}*/
