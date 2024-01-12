#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "View/View.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Controller
{
private:
    Controller();
    static Controller *instance;
    View *view;
    SDL_Window *window;
    Mix_Chunk *gMusic;
    bool isRunning;
    int mouseX, mouseY;
    void updateView(View *newView);

public:
    Controller(const Controller &) = delete;
    Controller &operator=(const Controller &) = delete;

    // Static method for accessing the singleton instance
    static Controller *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Controller();
        }
        return instance;
    }

    ~Controller();
    void run();
    void handleEvents();
};

#endif
