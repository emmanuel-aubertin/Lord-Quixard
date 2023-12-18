#ifndef VIEW_HPP
#define VIEW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class View {
protected:
    SDL_Window* window;
    SDL_Surface* windowSurface;

    std::string getWorkingDirectory();
public:
    View(SDL_Window* win);
    virtual ~View();

    virtual void render() = 0; 
    void clear();
    void display();
};

#endif
