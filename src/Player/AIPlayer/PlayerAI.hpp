#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include "../Player.hpp"
#include <vector>
#include "../../GameBoard/GameBoard.hpp"

class PlayerAI : public Player
{
public:
    PlayerAI(const std::string &name);
    virtual ~PlayerAI() = default;
    virtual std::vector<int> getPlay(GameBoard*);
};

#endif
