#ifndef MAGESMELEE_HPP
#define MAGESMELEE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../View.hpp"
#include <vector>
#include <utility>

class MageSMelee : public View {
public:
    MageSMelee(SDL_Window* win);
    virtual ~MageSMelee();
    void render() override;
private:
    View* handleClick(int, int) override;
};

#endif
