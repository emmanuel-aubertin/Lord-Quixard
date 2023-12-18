#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../View.hpp"

class MainMenu : public View {
public:
    MainMenu(SDL_Window* win);
    virtual ~MainMenu();

    void render() override;
private:
    TTF_Font* font;
    SDL_Surface* gHelloWorld;
    SDL_Surface *textSurface;
    SDL_Surface *window_surface;
    void renderText(const std::string &text, int x, int y, SDL_Color color, int size);
    // For FPS tracking
    Uint32 frameStart;
    int frameCount;
    int fps;
};

#endif
