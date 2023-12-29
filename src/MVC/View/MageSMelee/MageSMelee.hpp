#ifndef MAGESMELEE_HPP
#define MAGESMELEE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../View.hpp"
#include <vector>
#include <utility>
#include "../../../GameEngine/GameEngine.hpp"

class MageSMelee : public View
{
public:
    MageSMelee(SDL_Window *win);
    virtual ~MageSMelee();
    void render() override;
    bool hasUndo() override;

protected:
    static constexpr int NUM_TILES = 25; // Define NUM_TILES as a constant expression
    static TileCoords BACK_BTN;
    static TileCoords TILE_COORDS[NUM_TILES];
    int indexCliked;
    GameEngine *engine;
    bool isPointInTile(const SDL_Point &point, const TileCoords &tile);
    View *handleClick(int, int) override;
    SDL_Surface *backgroundSuface;
    SDL_Surface *window_surface;
    SDL_Surface *tileSurface;
    SDL_Surface *oSprite;
    SDL_Surface *xSprite;
    std::array<std::array<Tile, 5>, 5> board;
    // For FPS tracking
    Uint32 frameStart;
    int frameCount;
    int fps;
};

#endif
