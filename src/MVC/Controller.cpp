#include "Controller.hpp"
#include <iostream>
#include "View/MainMenu/MainMenu.hpp"
#include "../../Config.hpp"
#include <typeinfo>

Controller::Controller()
{
    SDL_GetMouseState(&mouseX, &mouseY);
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

    this->view = new MainMenu(window);
    isRunning = true;
}

Controller::~Controller()
{
    delete view;
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Controller::run()
{
    while (isRunning)
    {

        handleEvents();

        view->render();
        SDL_UpdateWindowSurface(window);

    }
}

void Controller::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            View *tempView = view->handleClick(mouseX, mouseY);
            if (tempView != nullptr)
            {
                updateView(tempView);
            }
            break;
        }
    }
}

void Controller::updateView(View* newView)
{
    SDL_FillRect(SDL_GetWindowSurface(window), NULL, SDL_MapRGB(SDL_GetWindowSurface(window)->format, 0, 0, 0));
    delete view;
    this->view = newView;
}
