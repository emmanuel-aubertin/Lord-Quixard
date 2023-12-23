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
#include <SDL2/SDL_mixer.h>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
    #include <direct.h>
    #define GETCWD _getcwd
#else
    #include <unistd.h>
    #define GETCWD getcwd
#endif

PlayVAi::PlayVAi(SDL_Window *win) : MageSMelee(win)
{
    PlayerHuman *playerOne = new PlayerHuman("Thalira Mooncrest");
    RandomAI *playerTwo = new RandomAI("Balthazard le Terryble");
    engine = new GameEngine(*playerOne, *playerTwo);
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    char buff[FILENAME_MAX];
    GETCWD(buff, FILENAME_MAX);

    srand(time(NULL));
    int randomInt = rand() % 2 + 1; 
    std::string pathWelcome = std::string(buff) + "/static/audio/balthazard.hello." + std::to_string(randomInt) + ".wav";


    Mix_Chunk* gWelcome = Mix_LoadWAV( pathWelcome.c_str() );
    if( gWelcome == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    Mix_VolumeChunk(gWelcome, 48);

    // Play music on a loop
    Mix_PlayChannel(-1, gWelcome, 0);
}

PlayVAi::~PlayVAi() {
}

View *PlayVAi::handleClick(int x, int y)
{
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
                engine->makeIAmove();
                engine->printBoard();
                board = engine->getBoard();
                indexCliked = -1;
                break;
            }
            if (coords.first == 0 || coords.first == 4 || coords.second == 0 || coords.second == 4)
            {
                indexCliked = i;
                break;
            }
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
