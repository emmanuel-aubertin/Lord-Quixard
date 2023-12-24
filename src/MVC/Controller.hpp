#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "Model.hpp"
#include "View/View.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


class Controller {
private:
    Model* model;
    View* view;
    SDL_Window* window;
    Mix_Chunk* gMusic;
    bool isRunning;
    int mouseX, mouseY;
    void updateView(View* newView);
public:
    Controller();
    ~Controller();
    void run();
    void handleEvents();
};

#endif 
