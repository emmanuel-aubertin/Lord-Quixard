#include "MainMenu.hpp"
#include "../MageSMelee/MageSMelee.hpp"
#include <iostream>
#include <array>
#include <utility>

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

    // Load font once
    std::string fontFile = getWorkingDirectory() + "/static/font/Norsebold.ttf";
    font = TTF_OpenFont(fontFile.c_str(), 128);
    if (!font)
    {
        std::cerr << "❌ Error: Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
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
    if (font)
    {
        TTF_CloseFont(font);
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
    // Define hexagon vertices
    std::vector<std::pair<int, int>> hexagonVertices = {
        {936, 690}, {1050, 626}, {1050, 484}, {939, 453}, {819, 485}, {822, 623}};

    // Check if mouse is inside hexagon
    if (isPointInPoly(mouseX, mouseY, hexagonVertices) && !isCube)
    {
        //std::cout << "x: " << mouseX << " y: " << mouseY << std::endl;
        // Load background image once
        std::string background_path = getWorkingDirectory() + "/static/img/CubeSprite.bmp";
        SDL_Surface *Cube = SDL_LoadBMP(background_path.c_str());
        if (!Cube)
        {
            std::cerr << "Unable to load image " << background_path << "! SDL Error: " << SDL_GetError() << std::endl;
            // Consider a more graceful error handling approach
        }

        if (Cube)
        {
            isCube = true;
            SDL_BlitSurface(Cube, NULL, windowSurface, NULL);
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


    renderText("Mage's Melee", 880, 420, textColor, 32);

    renderText("Magic Quixo", 20, 20, textColor, 124);
}


View* MainMenu::handleClick(int x, int y){
    std::vector<std::pair<int, int>> hexagonVertices = {
        {936, 690}, {1050, 626}, {1050, 484}, {939, 453}, {819, 485}, {822, 623}};
    if(isPointInPoly(x, y, hexagonVertices)) {
        std::cout << "In cube" << std::endl;
        return new MageSMelee(window);
    }
    return nullptr;
}