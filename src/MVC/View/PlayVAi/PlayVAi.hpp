#ifndef PLAYVAI_HPP
#define PLAYVAI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../View.hpp"
#include <vector>
#include <thread>
#include <utility>
#include "../../../GameEngine/GameEngine.hpp"
#include "../MageSMelee/MageSMelee.hpp"

class PlayVAi : public MageSMelee
{
public:
    PlayVAi(SDL_Window *win);
    virtual ~PlayVAi();
    void render() override;

private:
    int moveCounter, moveToPlay;
    std::thread aiThread;
    bool audioWin;
    void runAI();
    View *handleClick(int x, int y) override;
};

#endif
