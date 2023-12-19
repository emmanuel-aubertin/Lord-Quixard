#include "MageSMelee.hpp"
#include <iostream>
#include <array>
#include <utility>


MageSMelee::MageSMelee(SDL_Window *win) : View(win)
{
    frameStart = SDL_GetTicks();
    frameCount = 0;
    fps = 0;

    std::string background_path = getWorkingDirectory() + "/static/img/GameTable.bmp";
    backgroundSuface = SDL_LoadBMP(background_path.c_str());
    if (!backgroundSuface)
    {
        std::cerr << "Unable to load image " << background_path << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    if (backgroundSuface)
    {
        SDL_BlitSurface(backgroundSuface, NULL, windowSurface, NULL);
    }


}

MageSMelee::~MageSMelee()
{
    if (backgroundSuface)
    {
        SDL_FreeSurface(backgroundSuface);
    }
}

void MageSMelee::render()
{
    /*int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    std::cout << "x: " << mouseX << " y: " << mouseY << std::endl;*/
    frameCount++;
    Uint32 frameTime = SDL_GetTicks() - frameStart;

    if (frameTime >= 1000)
    {
        fps = frameCount;
        frameCount = 0;
        frameStart = SDL_GetTicks();
    }

    if (backgroundSuface)
    {
        SDL_Rect destRect = {0, 0, windowSurface->w, windowSurface->h};
        SDL_BlitScaled(backgroundSuface, NULL, windowSurface, &destRect);
    }



    SDL_Color textColor = {255, 255, 255};

    // Clear the previous FPS text
    SDL_Rect fpsRect = {1792 - 80, 5, 100, 30};
    SDL_BlitSurface(this->backgroundSuface, &fpsRect, windowSurface, &fpsRect);

    // Render the new FPS text

    std::string fpsText = "FPS: " + std::to_string(fps);
    renderText(fpsText, 1725, 5, textColor, 24);

    //renderText("Magic Quixo", 20, 20, textColor, 124);
}

struct TileCoords {
    SDL_Point topLeft;
    SDL_Point topRight;
    SDL_Point bottomRight;
    SDL_Point bottomLeft;
};

const int NUM_TILES = 25;
TileCoords tileCoords[NUM_TILES] = {
    {{710, 321}, {772, 319}, {773, 378}, {711, 377}},
    {{780, 320}, {841, 320}, {841, 378}, {780, 377}},
    {{847, 322}, {908, 322}, {908, 376}, {848, 378}},
    {{914, 322}, {975, 319}, {978, 378}, {914, 377}},
    {{982, 320}, {1044, 318}, {1045, 378}, {985, 378}},
    {{710, 387}, {772, 387}, {773, 444}, {709, 443}},
    {{779, 388}, {841, 387}, {842, 446}, {778, 443}},
    {{847, 388}, {909, 386}, {909, 443}, {847, 444}},
    {{914, 387}, {978, 386}, {978, 445}, {916, 447}},
    {{984, 389}, {1046, 388}, {1047, 445}, {985, 446}},
    {{708, 453}, {772, 452}, {773, 507}, {707, 505}},
    {{778, 452}, {841, 452}, {840, 506}, {777, 507}},
    {{847, 453}, {911, 452}, {911, 506}, {846, 507}},
    {{917, 455}, {979, 455}, {981, 506}, {918, 506}},
    {{985, 453}, {1047, 451}, {1050, 506}, {985, 505}},
    {{707, 514}, {772, 514}, {772, 571}, {707, 569}},
    {{777, 516}, {841, 515}, {841, 571}, {778, 570}},
    {{846, 515}, {910, 514}, {910, 573}, {849, 570}},
    {{917, 512}, {980, 512}, {982, 571}, {919, 571}},
    {{987, 514}, {1050, 513}, {1050, 570}, {988, 571}},
    {{706, 579}, {770, 579}, {770, 637}, {704, 637}},
    {{777, 580}, {841, 578}, {840, 637}, {776, 636}},
    {{848, 579}, {911, 579}, {912, 636}, {849, 637}},
    {{917, 579}, {981, 579}, {983, 638}, {916, 636}},
    {{989, 579}, {1051, 579}, {1053, 638}, {990, 640}}
};


bool isPointInTile(const SDL_Point& point, const TileCoords& tile) {
    return (point.x >= tile.topLeft.x && point.x <= tile.topRight.x &&
            point.y >= tile.topLeft.y && point.y <= tile.bottomLeft.y);
}


View *MageSMelee::handleClick(int x, int y)
{
SDL_Point clickedPoint = {x, y};
    for (int i = 0; i < NUM_TILES; ++i) {
        if (isPointInTile(clickedPoint, tileCoords[i])) {
            std::cout << "Clicked on tile " << i << std::endl;
            break;
        }
    }
    return nullptr;
}
