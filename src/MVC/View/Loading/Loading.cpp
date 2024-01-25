#include "Loading.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // Include SDL_image for JPEG support

Loading::Loading(SDL_Window *win) : View(win)
{
    imgCounter = 1;
    lastUpdateTime = 0;
    frameDuration = 1000 / 30;
}

Loading::~Loading()
{
}

bool Loading::hasUndo() { return false; }
void Loading::render()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastUpdateTime < frameDuration)
    {
        // Not enough time has passed since the last update
        return;
    }

    lastUpdateTime = currentTime; // Update the time of the last update

    std::string background_path = getFramePath(imgCounter);

    // Load the JPEG image using SDL_image
    SDL_Surface *gHelloWorld = IMG_Load(background_path.c_str());
    if (!gHelloWorld)
    {
        std::cerr << "Unable to load image " << background_path << "! SDL Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        SDL_BlitSurface(gHelloWorld, NULL, windowSurface, NULL);
        SDL_FreeSurface(gHelloWorld); // Free the surface after using it
    }

    // All the animation has been played
    if (imgCounter == 208)
    {
        imgCounter = 1;
    }
    else
    {
        imgCounter++;
    }
}

std::string Loading::getFramePath(int frameNumber)
{
    std::string path;
    if (frameNumber < 10)
    {
        path = getWorkingDirectory() + "/static/img/loading/frames_000" + std::to_string(frameNumber) + ".jpg"; // Use .jpg for JPEG
    }
    else if (frameNumber < 100)
    {
        path = getWorkingDirectory() + "/static/img/loading/frames_00" + std::to_string(frameNumber) + ".jpg"; // Use .jpg for JPEG
    }
    else
    {
        path = getWorkingDirectory() + "/static/img/loading/frames_0" + std::to_string(frameNumber) + ".jpg"; // Use .jpg for JPEG
    }
    return path;
}

View *Loading::handleClick(int, int)
{
    return nullptr;
}
