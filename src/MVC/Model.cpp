#include "Model.hpp";

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../Config.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#ifdef _WIN32
#include <direct.h>
#define GETCWD _getcwd
#else
#include <unistd.h>
#define GETCWD getcwd
#endif

Model::Model()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "❌ Error: Failed to initialize the SDL2 library ❌" << std::endl;
        exit(-1);
    }
    if (TTF_Init() == -1)
    {
        std::cerr << "❌ Error: SDL_ttf could not initialize. SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(-1);
    }

    this->window = SDL_CreateWindow(Config::PROGNAME.c_str(),
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    1792, 1024,
                                    0);

    if (!window)
    {
        std::cerr << "❌ Error: Failed to create window ❌" << std::endl;
        exit(-1);
    }

    this->window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        std::cerr << "❌ Error: Failed to get the surface from the window ❌" << std::endl;
        exit(-1);
    }
    frameStart = SDL_GetTicks();
    frameCount = 0;
    fps = 0;
    this->event;

    this->running = false;

    std::string background_path = getWorkingDirectory() + "/static/img/QuixoMainMenu.bmp";

    this->gHelloWorld = SDL_LoadBMP(background_path.c_str());
    if (this->gHelloWorld == NULL)
    {
        std::cerr << "Unable to load image " << background_path << "! SDL Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    SDL_BlitSurface(this->gHelloWorld, NULL, this->window_surface, NULL);

    std::string fontFile = getWorkingDirectory() + "/static/font/Norsebold.ttf";
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), 128);
    if (!font)
    {
        std::cerr << "❌ Error: Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
        exit(-1);
    }

    SDL_Color textColor = {255, 255, 255}; // White color
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "Magic Quixo", textColor);
    if (!textSurface)
    {
        std::cerr << "❌ Error: Unable to render text surface. SDL_ttf Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        exit(-1);
    }
    SDL_Rect textRect;
    textRect.x = (1792 - textSurface->w) / 2; // Center the text horizontally
    textRect.y = 10;                          // 10 pixels from the top

    SDL_BlitSurface(textSurface, NULL, this->window_surface, &textRect);

    // Free the surfaces and font
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

std::string Model::getWorkingDirectory()
{
    char buff[FILENAME_MAX];
    GETCWD(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

void Model::run() {
    this->running = true;
    while (this->running) {
        frameCount++;
        Uint32 frameTime = SDL_GetTicks() - frameStart;

        if (frameTime >= 1000) {
            fps = frameCount;
            frameCount = 0;
            frameStart = SDL_GetTicks();
        }

        while (SDL_PollEvent(&this->event)) {
            if (this->event.type == SDL_QUIT) {
                this->running = false;
            }
        }

        // Clear the previous FPS text
        SDL_Rect fpsRect = {1792 - 100, 10, 100, 30}; // Adjust the size as needed
        SDL_BlitSurface(this->gHelloWorld, &fpsRect, this->window_surface, &fpsRect);

        // Render the new FPS text
        SDL_Color textColor = {255, 255, 255}; 
        std::string fpsText = "FPS: " + std::to_string(fps);
        renderText(fpsText, 1792 - 100, 10, textColor, 24);

        SDL_UpdateWindowSurface(this->window);
    }
}


void Model::close()
{
    this->running = false;
    SDL_DestroyWindow(this->window);
    TTF_Quit();
    SDL_Quit();
}

void Model::renderText(const std::string &text, int x, int y, SDL_Color color, int size)
{
    std::string fontFile = getWorkingDirectory() + "/static/font/Norsebold.ttf";
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), size);
    if (!font)
    {
        std::cerr << "Error: Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface)
    {
        std::cerr << "Error: Unable to render text surface. SDL_ttf Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_BlitSurface(surface, NULL, window_surface, &destRect);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}