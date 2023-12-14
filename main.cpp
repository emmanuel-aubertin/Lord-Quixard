/***************************************************************************************/
/*----- Auteur :        Aubertin Emmanuel               |  For: Quixo               ****/
/*----- Description :   Quixo                                                       ****/
/*----- Contact :       https://athomisos.fr                                        ****/
/***************************************************************************************/

// ANSI escape codes for text color
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>

#include "src/GameEngine/GameEngine.hpp"
#include "src/Player/PlayerHuman/PlayerHuman.hpp"
#include "src/Player/AIPlayer/RandomAI/RandomAI.hpp"

std::string PROGNAME = "Quixo";
std::string FILE_NAME = __FILE__;
std::string RELEASE = "Revision 1.0 | Last update 13 december 2023";
std::string AUTHOR = "\033[1mAubertin Emmanuel\033[0m";
std::string COPYRIGHT = "(c) 2023 " + AUTHOR + " from https://athomisos.fr";
bool VERBOSE = false;

auto print_release = []
{
    std::cout << RELEASE << '\n'
              << COPYRIGHT << '\n';
};

auto failure = [](std::string_view message)
{
    std::cerr << "❌ Error: " << message << " ❌\n";
};

auto print_usage = []()
{
    std::cout << std::endl
              << PROGNAME << " by " << AUTHOR << std::endl
              << "\033[1mUsage: \033[0m" << FILE_NAME << " | [-h | --help] | [-v | --version] | [-V | --verbose] | [-s | --seq] | [-t | --threadpool] | [-p | --parallel-recursion] & [-f | --file] filename" << std::endl
              << "          -h            help" << std::endl
              << "          -v            Version" << std::endl
              << "          -v            Verbose" << std::endl;
};

auto print_help = []()
{
    print_release();
    std::cout << std::endl;
    print_usage();
    std::cout << std::endl
              << std::endl;
    exit(0);
};

int main(int argc, char **argv)
{
    std::cout << "🤗  |Welcome in \033[1m" << PROGNAME << "\033[0m mode| 🤗" << std::endl;
    print_release();
    std::cout << std::endl
              << std::endl;
    std::string filename = "";

    // Arg parser
    if (argc < 0) // number of arg minimum
        failure("One argument required. \n\t-h for help");

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            print_usage();
            exit(0);
        }
        else if (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--version"))
        {
            print_release();
            exit(0);
        }
        else if (!strcmp(argv[i], "-V") || !strcmp(argv[i], "--verbose"))
        {
            VERBOSE = true;
        }
        else
        { // ALL OTHER ARGUMENT
            print_usage();
            std::string arg = argv[i];
            std::string err = "Unknow argument : " + arg;
            failure(err);
        }
    }

    PlayerHuman *david = new PlayerHuman("David");
    RandomAI *roger = new RandomAI("Roger");

    GameEngine *engine = new GameEngine(*david, *roger);

    engine->printBoard();

    while (!engine->isWinner())
    {
        engine->makeIAmove();
    }

    engine->printBoard();

    /*
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            failure("Failed to initialize the SDL2 library\n");
            return -1;
        }

        SDL_Window *window = SDL_CreateWindow(PROGNAME.c_str(), // Cast PROGNAME from string to const char *
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              680, 480,
                                              0);

        if(!window) {
            failure("Failed to create window\n");
            return -1;
        }

        SDL_Surface *window_surface = SDL_GetWindowSurface(window);

        if(!window_surface) {
            failure("Failed to get the surface from the window\n");
            return -1;
        }

        SDL_Event event;
        bool running = true;

        while(running) {
            while(SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                }
            }
            SDL_UpdateWindowSurface(window);
        }

        SDL_DestroyWindow(window);
        SDL_Quit();*/
    return 0;
}
