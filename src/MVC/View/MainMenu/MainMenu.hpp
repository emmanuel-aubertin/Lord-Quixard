#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../View.hpp"
#include <SDL2/SDL_mixer.h>

class MainMenu : public View
{
public:
    MainMenu(SDL_Window *win);
    virtual ~MainMenu();

    void render() override;

private:
    bool isCube, isBal, isMinMax;
    TTF_Font *font;
    SDL_Surface *gHelloWorld;
    SDL_Surface *textSurface;
    SDL_Surface *window_surface;
    Mix_Chunk* gMageVmage;


    View *handleClick(int, int) override;
    // For FPS tracking
    Uint32 frameStart;
    int frameCount;
    int fps;
};

#endif
