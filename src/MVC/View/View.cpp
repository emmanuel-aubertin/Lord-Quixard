#include "View.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#ifdef _WIN32
#include <direct.h>
#define GETCWD _getcwd
#else
#include <unistd.h>
#define GETCWD getcwd
#endif

/**
 * @brief Construct a new View object.
 * Initializes the windowSurface by getting the surface from the provided SDL_Window.
 * Displays an error message if the window surface cannot be obtained.
 *
 * @param win Pointer to SDL_Window to be used for rendering.
 */

View::View(SDL_Window *win) : window(win)
{
    windowSurface = SDL_GetWindowSurface(window);
    if (!windowSurface)
    {
        std::cerr << "Error: Failed to get the window surface." << std::endl;
    }
}

/**
 * @brief Destructor for the View object.
 * Cleans up resources when the View object is destroyed.
 */

View::~View()
{
}

/**
 * @brief Clears the window surface.
 * Fills the window surface with black color (RGB 0, 0, 0).
 */

void View::clear()
{
    SDL_FillRect(windowSurface, NULL, SDL_MapRGB(windowSurface->format, 0, 0, 0));
}

/**
 * @brief Updates the window surface.
 * Displays the current contents of the window surface on the screen.
 */

void View::display()
{
    SDL_UpdateWindowSurface(window);
}

/**
 * @brief Retrieves the current working directory.
 * Returns a string representing the absolute path of the current working directory.
 *
 * @return std::string The current working directory path.
 */
std::string View::getWorkingDirectory()
{
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

/**
 * @brief Renders text on the window surface at specified coordinates.
 * Uses SDL_ttf to create a surface from the provided text and blits it onto the window surface.
 * Displays an error if the font fails to load or text surface cannot be rendered.
 *
 * @param text The string to be rendered.
 * @param x The x-coordinate where the text will be rendered.
 * @param y The y-coordinate where the text will be rendered.
 * @param color The color of the text.
 * @param size The font size for the text.
 */
void View::renderText(const std::string &text, int x, int y, SDL_Color color, int size)
{
    std::string fontFile = getWorkingDirectory() + "/static/font/Norsebold.ttf";
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), size);
    if (!font)
    {
        std::cerr << "Error: Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    // Splitting the string by newline character
    std::istringstream iss(text);
    std::string line;
    int yOffset = 0;
    while (std::getline(iss, line))
    {
        SDL_Surface *surface = TTF_RenderText_Solid(font, line.c_str(), color);
        if (!surface)
        {
            std::cerr << "Error: Unable to render text surface. SDL_ttf Error: " << TTF_GetError() << std::endl;
            continue;
        }

        SDL_Rect destRect = {x, y + yOffset, surface->w, surface->h};
        SDL_BlitSurface(surface, NULL, windowSurface, &destRect);
        yOffset += surface->h; // Move down for the next line

        SDL_FreeSurface(surface);
    }

    TTF_CloseFont(font);
}

/**
 * @brief Renders text centered horizontally on the window surface.
 * Similar to renderText but aligns the text in the center of the window.
 * The x-coordinate is calculated based on the window width and text dimensions.
 *
 * @param text The string to be rendered.
 * @param winWidth Width of the window for centering the text.
 * @param startY The starting y-coordinate for the text.
 * @param color The color of the text.
 * @param fontSize The size of the font.
 */
void View::renderCenteredText(const std::string &text, int winWidth, int startY, SDL_Color color, int fontSize)
{
    std::istringstream iss(text);
    std::string line;
    int y = startY;
    std::string fontFile = getWorkingDirectory() + "/static/font/Norsebold.ttf";
    TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (!font)
    {
        std::cerr << "Error: Failed to load font. SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    while (std::getline(iss, line))
    {
        int textWidth, textHeight;
        TTF_SizeText(font, line.c_str(), &textWidth, &textHeight);

        int x = (winWidth - textWidth) / 2;

        SDL_Surface *textSurface = TTF_RenderText_Solid(font, line.c_str(), color);
        if (!textSurface)
        {
            TTF_CloseFont(font);
            std::cerr << "Error: Unable to render text surface. SDL_ttf Error: " << TTF_GetError() << std::endl;
            return;
        }

        SDL_Rect textRect = {x, y, textWidth, textHeight};
        SDL_BlitSurface(textSurface, NULL, windowSurface, &textRect);
        SDL_FreeSurface(textSurface);

        y += textHeight; // Move to the next line position
    }

    TTF_CloseFont(font);
}

/**
 * @brief Loads an audio file.
 * Loads a WAV audio file from the specified path and sets its volume level.
 * Displays an error if the audio file cannot be loaded.
 *
 * @param filename The name of the audio file to load.
 * @param level The volume level for the audio.
 * @return Mix_Chunk* Pointer to the loaded audio chunk, or NULL if loading fails.
 */
Mix_Chunk *View::loadAudio(std::string filename, int level)
{
    filename = getWorkingDirectory() + "/static/audio/" + filename + ".wav";
    std::cout << filename << std::endl;
    Mix_Chunk *gAudio = Mix_LoadWAV(filename.c_str());
    if (gAudio == NULL)
    {
        printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    Mix_VolumeChunk(gAudio, level);
    return gAudio;
}

/**
 * @brief Plays an audio chunk on a specific audio channel.
 * Uses SDL_mixer to play the provided audio chunk.
 *
 * @param gAudio Pointer to the Mix_Chunk audio chunk to be played.
 * @param canal The audio channel on which to play the audio.
 */
void View::playAudio(Mix_Chunk *gAudio, int canal)
{
    Mix_PlayChannel(canal, gAudio, 0);
}

/**
 * @brief Loads and plays an audio file on a specific channel.
 * A convenience method that combines loading and playing of an audio file.
 *
 * @param filename The name of the audio file to load and play.
 * @param level The volume level for the audio.
 * @param canal The audio channel on which to play the audio.
 */
void View::playAudio(std::string filename, int level, int canal)
{
    Mix_PlayChannel(canal, loadAudio(filename, level), 0);
}