#include "MainMenu.hpp"
#include "../MageSMelee/MageSMelee.hpp"
#include "../PlayVAi/PlayVAi.hpp"
#include <iostream>
#include <array>
#include <utility>

const std::vector<std::pair<int, int>> CASTEL_POLY = {
    {1383, 264}, {1379, 216}, {1375, 233}, {1368, 223},
    {1364, 215}, {1358, 217}, {1355, 210}, {1352, 198},
    {1344, 216}, {1345, 205}, {1338, 196}, {1334, 185},
    {1324, 182}, {1319, 179}, {1308, 184}, {1299, 199},
    {1292, 217}, {1288, 196}, {1280, 218}, {1271, 223},
    {1262, 218}, {1260, 244}, {1259, 265}, {1279, 264},
    {1303, 262}
};

const std::vector<std::pair<int, int>> CUBE_POLY = {
        {936, 690}, {1050, 626}, {1050, 484}, {939, 453}, {819, 485}, {822, 623}};

MainMenu::MainMenu(SDL_Window *win) : View(win)
{
    isCube = false;
    frameStart = SDL_GetTicks();
    frameCount = 0;
    fps = 0;

    // Load background image once
    std::string background_path = getWorkingDirectory() + "/static/img/QuixoMainMenu.bmp";
    gHelloWorld = SDL_LoadBMP(background_path.c_str());
    if (!gHelloWorld)
    {
        std::cerr << "Unable to load image " << background_path << "! SDL Error: " << SDL_GetError() << std::endl;
        // Consider a more graceful error handling approach
    }

    if (gHelloWorld)
    {
        SDL_BlitSurface(gHelloWorld, NULL, windowSurface, NULL);
    }
}

MainMenu::~MainMenu()
{
    if (gHelloWorld)
    {
        SDL_FreeSurface(gHelloWorld);
    }
}

void MainMenu::render()
{
    frameCount++;
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (frameTime >= 1000)
    {
        fps = frameCount;
        frameCount = 0;
        frameStart = SDL_GetTicks();
    }
    if (gHelloWorld)
    {
        SDL_Rect destRect = {0, 0, windowSurface->w, windowSurface->h};
        SDL_BlitScaled(gHelloWorld, NULL, windowSurface, &destRect);
    }

    // Define hexagon vertices


    // Check if mouse is inside hexagon
    if (isPointInPoly(mouseX, mouseY, CUBE_POLY))
    {
        // std::cout << "x: " << mouseX << " y: " << mouseY << std::endl;
        //  Load background image once
        std::string background_path = getWorkingDirectory() + "/static/img/CubeSprite.bmp";
        SDL_Surface *Cube = SDL_LoadBMP(background_path.c_str());
        if (!Cube)
        {
            std::cerr << "Unable to load image " << background_path << "! SDL Error: " << SDL_GetError() << std::endl;
            // Consider a more graceful error handling approach
        }

        if (Cube)
        {
            SDL_BlitSurface(Cube, NULL, windowSurface, NULL);
        }
    }

    if (isPointInPoly(mouseX, mouseY, CASTEL_POLY))
    {
        // std::cout << "x: " << mouseX << " y: " << mouseY << std::endl;
        //  Load background image once
        std::string background_path = getWorkingDirectory() + "/static/img/CastelSprite.bmp";
        SDL_Surface *CastelSurf = SDL_LoadBMP(background_path.c_str());
        if (!CastelSurf)
        {
            std::cerr << "Unable to load image " << background_path << "! SDL Error: " << SDL_GetError() << std::endl;
            // Consider a more graceful error handling approach
        }

        if (CastelSurf)
        {
            SDL_BlitSurface(CastelSurf, NULL, windowSurface, NULL);
        }
    }
    else if (isCube)
    {
        const SDL_Rect cubeRect = {700, 350, 500, 500};
        SDL_Rect dstRect = {700, 350, 500, 500};

        if (SDL_BlitSurface(this->gHelloWorld, &cubeRect, windowSurface, &dstRect) < 0)
        {
            std::cerr << "SDL_BlitSurface error: " << SDL_GetError() << std::endl;
        }
        isCube = false;
    }

    // Clear the previous FPS text
    SDL_Rect fpsRect = {1792 - 80, 5, 100, 30};
    SDL_BlitSurface(this->gHelloWorld, &fpsRect, windowSurface, &fpsRect);
    SDL_Color textColor = {255, 255, 255};
    // Render the new FPS text
    std::string fpsText = "FPS: " + std::to_string(fps);
    renderText(fpsText, 1725, 5, textColor, 24);

    renderText("Affrontement Magique", 723, 390, textColor, 64);
    renderCenteredText("Repaire de l'Anomalie\nHasardeuse", 2650, 100, textColor, 32);
    renderText("Lord Quixard", 20, 20, textColor, 124);
}

View *MainMenu::handleClick(int x, int y)
{
    std::cout << "{" << x << ", "<< y  << "} " << std::endl;
    std::vector<std::pair<int, int>> CUBE_POLY = {
        {936, 690}, {1050, 626}, {1050, 484}, {939, 453}, {819, 485}, {822, 623}};
    if (isPointInPoly(x, y, CUBE_POLY))
    {
        std::cout << "In cube" << std::endl;
        return new MageSMelee(window);
    }
    if (isPointInPoly(x, y, CASTEL_POLY))
    {
        std::cout << "In cube" << std::endl;
        return new PlayVAi(window);
    }
    return nullptr;
}

/*
// The following section is here to get all coords for a custom (not regular) grid.
int tileNum = 0;
int pointCounter = -1;
View *MainMenu::handleClick(int x, int y)
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