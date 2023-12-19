#include "MageSMelee.hpp"
#include <iostream>
#include <array>
#include <utility>

const int GRID_SIZE = 5;
const int TILE_SIZE = 110;
const int gridWidth = GRID_SIZE * TILE_SIZE;
const int gridHeight = GRID_SIZE * TILE_SIZE;
const int startX = 647;
const int startY = 232;

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

    std::string tile_path = getWorkingDirectory() + "/static/img/EmptyTile.bmp";
    tileSurface = SDL_LoadBMP(tile_path.c_str());
    if (!tileSurface)
    {
        std::cerr << "Unable to load image " << tile_path << "! SDL Error: " << SDL_GetError() << std::endl;
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

    if (tileSurface)
    {
        for (int row = 0; row < GRID_SIZE; ++row)
        {
            for (int col = 0; col < GRID_SIZE; ++col)
            {
                SDL_Rect destRect = {startX + col * TILE_SIZE, startY + row * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                SDL_BlitSurface(tileSurface, NULL, windowSurface, &destRect);
            }
        }
    }

    SDL_Color textColor = {255, 255, 255};

    // Clear the previous FPS text
    SDL_Rect fpsRect = {1792 - 80, 5, 100, 30};
    SDL_BlitSurface(this->backgroundSuface, &fpsRect, windowSurface, &fpsRect);

    // Render the new FPS text

    std::string fpsText = "FPS: " + std::to_string(fps);
    //renderText(fpsText, 1725, 5, textColor, 24);

    //renderText("Magic Quixo", 20, 20, textColor, 124);
}

View *MageSMelee::handleClick(int x, int y)
{
    int col = (x - startX) / TILE_SIZE;
    int row = (y - startY) / TILE_SIZE;

    // Check if the click is within the grid bounds
    if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE)
    {
        // Calculate the tile number (0-based index)
        int tileNumber = row * GRID_SIZE + col;

        // TODO: Perform your action based on the clicked tile
        std::cout << "Clicked on tile number: " << tileNumber << " (" << row << ", " << col << ")" << std::endl;
    }
    else
    {
        std::cout << "Clicked outside of the grid." << std::endl;
    }

    return nullptr;
}
