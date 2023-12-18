#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu(SDL_Window* win) : View(win) {
    frameStart = SDL_GetTicks();
    frameCount = 0;
    fps = 0;

    // Load background image once
    std::string background_path = getWorkingDirectory() + "/static/img/QuixoMainMenu.bmp";
    gHelloWorld = SDL_LoadBMP(background_path.c_str());
    if (!gHelloWorld) {
        std::cerr << "Unable to load image " << background_path << "! SDL Error: " << SDL_GetError() << std::endl;
        // Consider a more graceful error handling approach
    }   

    // Load font once
    std::string fontFile = getWorkingDirectory() + "/static/font/Norsebold.ttf";
    font = TTF_OpenFont(fontFile.c_str(), 128);
    if (!font) {
        std::cerr << "❌ Error: Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
    }

    if (gHelloWorld) {
        SDL_BlitSurface(gHelloWorld, NULL, windowSurface, NULL);
    }
}

MainMenu::~MainMenu() {
    if (gHelloWorld) {
        SDL_FreeSurface(gHelloWorld);
    }
    if (font) {
        TTF_CloseFont(font);
    }
}

void MainMenu::render() {
    frameCount++;
    Uint32 frameTime = SDL_GetTicks() - frameStart;

    if (frameTime >= 1000) {
        fps = frameCount;
        frameCount = 0;
        frameStart = SDL_GetTicks();
    }



    // Clear the previous FPS text
    SDL_Rect fpsRect = {1792 - 80, 5, 100, 30}; 
    SDL_BlitSurface(this->gHelloWorld, &fpsRect, windowSurface, &fpsRect);
    SDL_Color textColor = {255, 255, 255};
    // Render the new FPS text
    std::string fpsText = "FPS: " + std::to_string(fps);
    renderText(fpsText, 1725, 5, textColor, 24);
    renderText("Magic Quixo", 573, 10, textColor, 128);

}

void MainMenu::renderText(const std::string &text, int x, int y, SDL_Color color, int size)
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
    SDL_BlitSurface(surface, NULL, windowSurface, &destRect);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}