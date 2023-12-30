#ifndef VIEW_HPP
#define VIEW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <utility>
#include <SDL2/SDL_mixer.h>

struct TileCoords
{
    SDL_Point topLeft;
    SDL_Point topRight;
    SDL_Point bottomRight;
    SDL_Point bottomLeft;
};

class View
{
protected:
    SDL_Window *window;
    SDL_Surface *windowSurface;
    void renderText(const std::string &text, int x, int y, SDL_Color color, int size);
    bool isPointInPoly(int x, int y, const std::vector<std::pair<int, int>> &poly);
    void renderCenteredText(const std::string &text, int winWidth, int startY, SDL_Color color, int fontSize);
    Mix_Chunk *loadAudio(std::string filename, int level);
    void playAudio(std::string filename, int level, int canal);
    void playAudio(Mix_Chunk *gAudio, int canal);
    std::string getWorkingDirectory();
    
public:
    View(SDL_Window *win);
    virtual ~View();
    virtual void undo() = 0;
    virtual View *handleClick(int, int) = 0;
    virtual bool hasUndo() = 0;
    virtual void render() = 0;
    void clear();
    void display();
};

#endif
