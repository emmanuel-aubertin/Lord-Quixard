#ifndef MINMAX_HPP
#define MINMAX_HPP

#include "../PlayerAI.hpp"
#include <vector>
#include "../../../GameBoard/GameBoard.hpp"

class MinMaxAI : public PlayerAI
{
public:
    MinMaxAI(const std::string &name);
    virtual ~MinMaxAI();
    std::vector<int> getPlay(GameBoard *);

private:
    int minimax(GameBoard *board, int depth, bool isMaximizingPlayer);
    int evaluateBoard(GameBoard *board);
};

#endif
