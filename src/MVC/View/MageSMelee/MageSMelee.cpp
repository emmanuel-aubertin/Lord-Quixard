#include "MageSMelee.hpp"
#include <iostream>
#include <array>
#include <utility>


MageSMelee::MageSMelee(SDL_Window *win) : View(win)
{
    frameStart = SDL_GetTicks();
    frameCount = 0;
    fps = 0;

    std::string background_path = getWorkingDirectory() + "/static/img/GameTable.bmp";
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



    SDL_Color textColor = {255, 255, 255};

    // Clear the previous FPS text
    SDL_Rect fpsRect = {1792 - 80, 5, 100, 30};
    SDL_BlitSurface(this->backgroundSuface, &fpsRect, windowSurface, &fpsRect);

    // Render the new FPS text

    std::string fpsText = "FPS: " + std::to_string(fps);
    renderText(fpsText, 1725, 5, textColor, 24);

    //renderText("Magic Quixo", 20, 20, textColor, 124);
}

const int NUM_TILES = 25;
TileCoords tileCoords[NUM_TILES] = {
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
    {{1012, 512}, {1081, 513}, {1088, 565}, {1017, 565}}
};


bool MageSMelee::isPointInTile(const SDL_Point& point, const TileCoords& tile) {
    return (point.x >= tile.topLeft.x && point.x <= tile.topRight.x &&
            point.y >= tile.topLeft.y && point.y <= tile.bottomLeft.y);
}


View *MageSMelee::handleClick(int x, int y)
{
SDL_Point clickedPoint = {x, y};
    for (int i = 0; i < NUM_TILES; ++i) {
        if (isPointInTile(clickedPoint, tileCoords[i])) {
            std::cout << "Clicked on tile " << i << std::endl;
            break;
        }
    }
    return nullptr;
}
/*
int tileNum = 0;
int pointCounter = -1;
View *MageSMelee::handleClick(int x, int y)
{
    pointCounter++;
    if(pointCounter == 0){
        std::cout <<"tile " << tileNum << ": {" << x << ", "<< y  << "} ";
        return nullptr;
    } 
    if(pointCounter == 3){
        std::cout << "{" << x << ", "<< y  << "} " << std::endl;
        tileNum++;
        pointCounter =-1 ;
        return nullptr;
    } 
    std::cout << "{" << x << ", "<< y  << "}, ";

    

    return nullptr;
}*/
