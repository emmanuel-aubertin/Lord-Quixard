#include <vector>
#include "./RandomAI.hpp"
#include <random>
#include <chrono>

/**
 * @brief Construct a new RandomAI object.
 * Initializes the RandomAI player with the given name. The constructor is currently placeholder
 * for potential future features specific to RandomAI.
 *
 * @param name The name of the RandomAI player.
 */
RandomAI::RandomAI(const std::string &name) : PlayerAI(name)
{
    // Waiting for new feature
}

/**
 * @brief Generates a random play for the AI player.
 * Creates a random move using a uniform distribution. The move is determined by randomly
 * selecting positions on the game board. If a randomly generated number is odd, the move
 * is along the same row; otherwise, it's along the same column.
 *
 * @return std::vector<int> The AI player's randomly chosen move, represented as a vector {x, y, new_x, new_y}.
 */
std::vector<int> RandomAI::getPlay(GameBoard *, Tile::Sign)
{
    std::vector<int> randomIntegers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> ran_big(1, 100);
    std::uniform_int_distribution<> edge_dis(0, 4);
    std::uniform_int_distribution<> middle_dis(1, 3);

    int ran_x = edge_dis(gen);
    int ran_y = (ran_x == 0 || ran_x == 4) ? edge_dis(gen) : middle_dis(gen);

    randomIntegers.push_back(ran_x);
    randomIntegers.push_back(ran_y);

    if (ran_big(gen) % 2 == 1)
    {
        randomIntegers.push_back(ran_x);
        randomIntegers.push_back(ran_y == 4 ? 0 : 4);
    }
    else
    {
        randomIntegers.push_back(ran_x == 4 ? 0 : 4);
        randomIntegers.push_back(ran_y);
    }

    return randomIntegers;
}