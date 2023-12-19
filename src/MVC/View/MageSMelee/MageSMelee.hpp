#ifndef MAGESMELEE_HPP
#define MAGESMELEE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../View.hpp"
#include <vector>
#include <utility>

struct TileCoords {
    SDL_Point topLeft;
    SDL_Point topRight;
    SDL_Point bottomRight;
    SDL_Point bottomLeft;
};

class MageSMelee : public View
{
public:
    MageSMelee(SDL_Window *win);
    virtual ~MageSMelee();
    void render() override;

private:
    bool isPointInTile(const SDL_Point &point, const TileCoords &tile);
    View *handleClick(int, int) override;
    SDL_Surface *backgroundSuface;
    SDL_Surface *window_surface;
    SDL_Surface *tileSurface;
    // For FPS tracking
    Uint32 frameStart;
    int frameCount;
    int fps;
};

#endif
