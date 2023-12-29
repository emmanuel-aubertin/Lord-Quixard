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
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    char buff[FILENAME_MAX];
    GETCWD(buff, FILENAME_MAX);
    audioWin = false;
    srand(time(NULL));
    int randomInt = rand() % 2 + 1;
    playAudio(loadAudio("balthazard/balthazard.hello." + std::to_string(randomInt), 48), 5);
    moveCounter = 0;
    moveToPlay = 4 + rand() % 4;
}

void PlayVAi::runAI()
{
    engine->makeIAmove();
    board = engine->getBoard();
}

PlayVAi::~PlayVAi()
{
    if (aiThread.joinable())
    {
        aiThread.join();
    }
}
void PlayVAi::render()
{
    MageSMelee::render();
    if (engine->isWinner() && !audioWin)
    {
        int randomInt = rand() % 2 + 1;

        if (engine->getWichSignPlay() == Tile::O)
        {
            playAudio(loadAudio("balthazard/balthazard.loose." + std::to_string(randomInt), 48), 6);
        }
        else
        {
            playAudio(loadAudio("balthazard/balthazard.win." + std::to_string(randomInt), 48), 6);
        }
        audioWin = true;
    }
}

View *PlayVAi::handleClick(int x, int y)
{
    SDL_Point clickedPoint = {x, y};
    if (isPointInTile(clickedPoint, BACK_BTN))
    {
        if (Mix_Playing(5))
        {
            Mix_HaltChannel(5);
        }
        return new MainMenu(window);
    }

    if (engine->isWinner())
    {
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
                moveCounter++;
                if (moveCounter % moveToPlay == 0)
                {
                    moveToPlay = 4 + rand() % 4;
                    int randomInt = rand() % 3 + 1;
                    playAudio(loadAudio("balthazard/balthazard.play." + std::to_string(randomInt), 48), 6);
                }
                board = engine->getBoard();
                if (engine->isWinner())
                {
                    indexCliked = -1;
                    break;
                }

                // Start AI thread
                if (aiThread.joinable())
                {
                    aiThread.join();
                }
                aiThread = std::thread(&PlayVAi::runAI, this);

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
