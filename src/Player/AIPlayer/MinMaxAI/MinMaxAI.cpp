#include "MinMaxAI.hpp"
#include "../../../GameBoard/GameBoard.hpp"

MinMaxAI::MinMaxAI(const std::string &name) : PlayerAI(name)
{
    // Initialization code, if necessary
}

MinMaxAI::~MinMaxAI()
{
    // Cleanup code, if necessary
}

int MinMaxAI::evaluateBoard(GameBoard *board)
{
    return 0;
}

int MinMaxAI::minimax(GameBoard *board, int depth, bool isMaximizingPlayer)
{

}

std::vector<int> MinMaxAI::getPlay(GameBoard *board)
{
    int bestValue = INT_MIN;
    std::vector<int> bestMove;
    return bestMove;
}
