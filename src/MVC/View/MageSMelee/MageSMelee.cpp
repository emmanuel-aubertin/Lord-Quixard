#include "MageSMelee.hpp"
#include <iostream>
#include <array>
#include <utility>

MageSMelee::MageSMelee(SDL_Window *win) : View(win)
{
}

MageSMelee::~MageSMelee()
{

}

void MageSMelee::render()
{
    SDL_Color textColor = {255, 255, 255};
    renderText("Magic Quixo", 20, 20, textColor, 124);
}


View* MageSMelee::handleClick(int x, int y){
    return nullptr;
}