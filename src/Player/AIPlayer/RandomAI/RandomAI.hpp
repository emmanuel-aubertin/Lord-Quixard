#ifndef RANDOMAI_HPP
#define RANDOMAI_HPP

#include <vector>
#include "../PlayerAI.hpp"

class RandomAI : public PlayerAI
{
public:
    RandomAI(const std::string &name);
    std::vector<int> getPlay(GameBoard *, Tile::Sign) override;
};
#endif