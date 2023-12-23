#include "MageSMelee.hpp"
#include <iostream>
#include <array>
#include <utility>
#include "../../../Player/PlayerHuman/PlayerHuman.hpp"
#include "../MainMenu/MainMenu.hpp"
#include "../../../Tile.cpp"
#include "../View.hpp"

TileCoords MageSMelee::BACK_BTN = {{0, 0}, {278, 0}, {0, 55}, {278, 55}};
TileCoords MageSMelee::TILE_COORDS[NUM_TILES] = {
    {{753, 323}, {813, 323}, {812, 363}, {749, 366}},
    {{815, 325}, {875, 324}, {873, 365}, {812, 365}},
    {{877, 324}, {935, 325}, {937, 365}, {876, 365}},
    {{938, 324}, {997, 325}, {1000, 366}, {941, 366}},
    {{999, 326}, {1059, 324}, {1065, 366}, {1002, 365}},
    {{749, 368}, {811, 367}, {809, 409}, {743, 408}},
    {{812, 368}, {873, 367}, {872, 408}, {810, 408}},
    {{875, 367}, {937, 367}, {938, 407}, {875, 408}},
    {{939, 367}, {1000, 366}, {1003, 407}, {940, 407}},
    {{1002, 366}, {1063, 367}, {1068, 407}, {1005, 406}},
    {{742, 411}, {804, 409}, {801, 457}, {735, 457}},
    {{809, 410}, {871, 410}, {870, 457}, {805, 456}},
    {{875, 410}, {938, 411}, {938, 456}, {873, 456}},
    {{940, 409}, {1003, 409}, {1007, 457}, {940, 456}},
    {{1005, 411}, {1068, 412}, {1075, 456}, {1008, 457}},
    {{735, 460}, {801, 460}, {797, 511}, {728, 510}},
    {{804, 459}, {869, 458}, {868, 512}, {802, 511}},
    {{873, 459}, {938, 459}, {940, 510}, {871, 510}},
    {{941, 459}, {1007, 459}, {1011, 512}, {942, 509}},
    {{1009, 459}, {1073, 459}, {1080, 511}, {1013, 510}},
    {{728, 513}, {796, 514}, {792, 567}, {718, 566}},
    {{799, 513}, {866, 512}, {866, 566}, {796, 566}},
    {{870, 512}, {938, 511}, {940, 565}, {869, 565}},
    {{942, 511}, {1011, 512}, {1014, 565}, {944, 564}},
    {{1012, 512}, {1081, 513}, {1088, 565}, {1017, 565}}};

MageSMelee::MageSMelee(SDL_Window *win) : View(win)
{
    
    indexCliked = -1;
    PlayerHuman *playerOne = new PlayerHuman("Thalira Mooncrest");
    PlayerHuman *playerTwo = new PlayerHuman("Cedric Frostshard");
    engine = new GameEngine(*playerOne, *playerTwo);

    frameStart = SDL_GetTicks();
    frameCount = 0;
    fps = 0;

    std::string background_path = getWorkingDirectory() + "/static/img/GameTable.bmp";
    std::string x_path = getWorkingDirectory() + "/static/img/XSprite.bmp";
    std::string o_path = getWorkingDirectory() + "/static/img/OSprite.bmp";
    oSprite = SDL_LoadBMP(o_path.c_str());
    xSprite = SDL_LoadBMP(x_path.c_str());
    backgroundSuface = SDL_LoadBMP(background_path.c_str());
    if (!backgroundSuface)
    {
        std::cerr << "Unable to load image " << background_path << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    if (backgroundSuface)
    {
        SDL_BlitSurface(backgroundSuface, NULL, windowSurface, NULL);
    }
}

MageSMelee::~MageSMelee()
{
    if (backgroundSuface)
    {
        SDL_FreeSurface(backgroundSuface);
    }
    if (xSprite) {
        SDL_FreeSurface(xSprite);
    }
    if (oSprite) {
        SDL_FreeSurface(oSprite);
    }
}

void MageSMelee::render()
{
    /*int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    std::cout << "x: " << mouseX << " y: " << mouseY << std::endl;*/
    frameCount++;
    Uint32 frameTime = SDL_GetTicks() - frameStart;

    if (frameTime >= 1000)
    {
        fps = frameCount;
        frameCount = 0;
        frameStart = SDL_GetTicks();
    }

    if (backgroundSuface)
    {
        SDL_Rect destRect = {0, 0, windowSurface->w, windowSurface->h};
        SDL_BlitScaled(backgroundSuface, NULL, windowSurface, &destRect);
    }
    

    int index = 0;
    for (const auto &row : board)
    {
        for (const auto &tile : row)
        {
            if(tile.sign == Tile::Blank) {index++;continue;}
            // Calculate the center of the tile
            int centerX = (TILE_COORDS[index].topLeft.x + TILE_COORDS[index].topRight.x) / 2;
            int centerY = (TILE_COORDS[index].topLeft.y + TILE_COORDS[index].bottomLeft.y) / 2;

            // Create a new rect to center the 40x40 sprite within the tile
            SDL_Rect spriteRect;
            spriteRect.w = 40;
            spriteRect.h = 40;
            spriteRect.x = centerX - spriteRect.w / 2;  
            spriteRect.y = centerY - spriteRect.h / 2;  

            if (tile.sign == Tile::X) {
                SDL_BlitSurface(xSprite, NULL, windowSurface, &spriteRect);
            } else if (tile.sign == Tile::O) {
                SDL_BlitSurface(oSprite, NULL, windowSurface, &spriteRect);
            }
            index++;
        }
    }

    SDL_Color textColor = {255, 255, 255};

    // Clear the previous FPS text
    SDL_Rect fpsRect = {1792 - 80, 5, 100, 30};
    SDL_BlitSurface(this->backgroundSuface, &fpsRect, windowSurface, &fpsRect);

    // Render the new FPS text

    std::string fpsText = "FPS: " + std::to_string(fps);
    renderText(fpsText, 1725, 5, textColor, 24);

    renderText("Back to artifact valley", 20, 20, textColor, 32);
    if(engine->isWinner()) {
        engine->getWinner();
        renderText("GG", 500, 20, textColor, 256);
    }

}

bool MageSMelee::isPointInTile(const SDL_Point &point, const TileCoords &tile)
{
    return (point.x >= tile.topLeft.x && point.x <= tile.topRight.x &&
            point.y >= tile.topLeft.y && point.y <= tile.bottomLeft.y);
}

View *MageSMelee::handleClick(int x, int y)
{
    //std::cout << "cliked : " << x << ", " << y << std::endl;
    SDL_Point clickedPoint = {x, y};
    if (isPointInTile(clickedPoint, BACK_BTN))
    {
        return new MainMenu(window);
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
                engine->printBoard();
                board = engine->getBoard();
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
