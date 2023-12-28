#include <vector>
#include "./RandomAI.hpp"
#include <random>
#include <chrono>

RandomAI::RandomAI(const std::string &name) : PlayerAI(name)
{
    // Waiting for new feature
}

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