#ifndef MINMAX_HPP
#define MINMAX_HPP

#include "../PlayerAI.hpp"
#include <vector>
#include "../../../GameBoard/GameBoard.hpp"

class MinMaxAI : public PlayerAI
{
public:
    MinMaxAI(const std::string &name);
    MinMaxAI(const std::string &name, int depth);
    virtual ~MinMaxAI();
    std::vector<int> getPlay(GameBoard *, Tile::Sign);

private:
    Tile::Sign oppositeSign(Tile::Sign sign);
    int minimax(GameBoard *board, int depth, bool isMaximizingPlayer, Tile::Sign sign);
    int evaluateBoard(GameBoard *board, Tile::Sign sign);
    int depth;
    int evaluateLine(const std::array<std::array<Tile, 5>, 5> &board,
                     int xStart, int yStart, int xStep, int yStep,
                     Tile::Sign sign);
};

#endif
