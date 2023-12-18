#ifndef MODEL_HPP
#define MODEL_HPP

#include <SDL2/SDL.h>
#include <string>

class Model
{
public:
    Model();
    void run();
    void close();
private:
    std::string getWorkingDirectory();
    SDL_Window *window;
    SDL_Surface *window_surface;
    SDL_Event event;
    bool running;
    SDL_Surface* gHelloWorld;
    void renderText(const std::string& text, int x, int y, SDL_Color color, int size);
    // For FPS tracking
    Uint32 frameStart;
    int frameCount;
    int fps;

};
#endif