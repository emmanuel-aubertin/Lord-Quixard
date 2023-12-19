#include "View.hpp"
#include <iostream>
#include <vector>
#include <utility>
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

/**
 * @brief Know if point is in the polygon. This method use Ray-casting algorythm. 
 * More here: https://rosettacode.org/wiki/Ray-casting_algorithm
 * 
 * @param x Point Coord
 * @param y Point Coord
 * @param poly All point that define your polygone
 * @return true If the point is inside
 * @return false If the point is outside
 */
bool View::isPointInPoly(int x, int y, const std::vector<std::pair<int, int>> &poly)
{
    bool inside = false;
    for (size_t i = 0, j = poly.size() - 1; i < poly.size(); j = i++)
    {
        int xi = poly[i].first, yi = poly[i].second;
        int xj = poly[j].first, yj = poly[j].second;

        bool intersect = ((yi > y) != (yj > y)) && (x < (xj - xi) * (y - yi) / (yj - yi) + xi);
        if (intersect)
        {
            inside = !inside;
        }
    }
    return inside;
}


void View::renderText(const std::string &text, int x, int y, SDL_Color color, int size)
{
    std::string fontFile = getWorkingDirectory() + "/static/font/Norsebold.ttf";
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), size);
    if (!font)
    {
        std::cerr << "Error: Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface)
    {
        std::cerr << "Error: Unable to render text surface. SDL_ttf Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_BlitSurface(surface, NULL, windowSurface, &destRect);

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}
