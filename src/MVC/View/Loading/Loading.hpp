#ifndef LOADING_HPP
#define LOADING_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../View.hpp"
#include <SDL2/SDL_mixer.h>

class Loading : public View
{
public:
    Loading(SDL_Window *win);
    virtual ~Loading();

    void render() override;
    bool hasUndo() override;

private:
    std::string getFramePath(int frameNumber);
    int imgCounter, frameDuration, lastUpdateTime;
    View *handleClick(int, int);
};

#endif
