#include "View.hpp"
#include <iostream>
#include <iostream>
#ifdef _WIN32
    #include <direct.h>
    #define GETCWD _getcwd
#else
    #include <unistd.h>
    #define GETCWD getcwd
#endif

View::View(SDL_Window* win) : window(win) {
    windowSurface = SDL_GetWindowSurface(window);
    if (!windowSurface) {
        std::cerr << "Error: Failed to get the window surface." << std::endl;
    }
}

View::~View() {
}

void View::clear() {
    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0, 0, 0));
}

void View::display() {
    SDL_UpdateWindowSurface(window);
}


std::string View::getWorkingDirectory() {
    char buff[FILENAME_MAX];
    GETCWD(buff, FILENAME_MAX);
    return std::string(buff);
}
