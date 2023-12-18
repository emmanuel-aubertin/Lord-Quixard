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
#include "src/MVC/Controller.hpp"
#include "Config.hpp"

bool VERBOSE = false;

auto print_release = []
{
    std::cout << Config::RELEASE << '\n'
              << Config::COPYRIGHT << '\n';
};

auto failure = [](std::string_view message)
{
    std::cerr << "❌ Error: " << message << " ❌\n";
};

auto print_usage = []()
{
    std::cout << std::endl
              << Config::PROGNAME << " by " << Config::AUTHOR << std::endl
              << "\033[1mUsage: \033[0m" << Config::PROGNAME << " | [-h | --help] | [-v | --version] | [-V | --verbose] | [-s | --seq] | [-t | --threadpool] | [-p | --parallel-recursion] & [-f | --file] filename" << std::endl
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
    std::cout << "🤗  | Welcome in \033[1m" << Config::PROGNAME << "\033[0m | 🤗" << std::endl;
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


    Controller* c = new Controller();
    
    c->run();
    
    return 0;
}