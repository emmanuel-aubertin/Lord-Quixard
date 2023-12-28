#include "MinMaxAI.hpp"
#include "../../../GameBoard/GameBoard.hpp"
#include <thread>
#include <future>
#include <algorithm>

MinMaxAI::MinMaxAI(const std::string &name) : PlayerAI(name)
{
    depth = 3;
}

MinMaxAI::MinMaxAI(const std::string &name, int depth) : PlayerAI(name)
{
    this->depth = depth;
}

MinMaxAI::~MinMaxAI()
{
    // Cleanup code, if necessary
}

int MinMaxAI::evaluateBoard(GameBoard *board, Tile::Sign sign)
{
    auto currentBoard = board->getBoard();
    int score = 0;

    // Check all rows, columns, and diagonals
    for (int i = 0; i < 5; ++i)
    {
        score += evaluateLine(currentBoard, i, 0, 0, 1, sign); // Row
        score += evaluateLine(currentBoard, 0, i, 1, 0, sign); // Column
    }
    score += evaluateLine(currentBoard, 0, 0, 1, 1, sign);  // Diagonal
    score += evaluateLine(currentBoard, 0, 4, 1, -1, sign); // Other diagonal

    return score;
}

int MinMaxAI::evaluateLine(const std::array<std::array<Tile, 5>, 5> &board,
                           int xStart, int yStart, int xStep, int yStep,
                           Tile::Sign sign)
{
    int countSign = 0;
    int countOpponent = 0;

    for (int i = 0; i < 5; ++i)
    {
        Tile::Sign currentSign = board[xStart + i * xStep][yStart + i * yStep].sign;
        if (currentSign == sign)
        {
            countSign++;
        }
        else if (currentSign != Tile::Sign::Blank)
        {
            countOpponent++;
        }
    }

    if (countSign == 5)
        return 10000; // Winning condition for the AI
    if (countOpponent == 5)
        return -10000; // Winning condition for the opponent

    return countSign - countOpponent; // Basic scoring
}

int MinMaxAI::minimax(GameBoard *board, int depth, bool isMaximizingPlayer, Tile::Sign sign)
{
    // Base case: if depth is 0 or game is over
    if (depth == 0)
    {
        return evaluateBoard(board, sign);
    }

    if (isMaximizingPlayer)
    {
        int bestValue = INT_MIN;
        for (const auto &move : board->getPossibleMoves(sign))
        {
            GameBoard tempBoard = *board;
            if (!tempBoard.move(move, sign))
                continue;
            int moveValue = minimax(&tempBoard, depth - 1, false, sign); // Decrease depth and switch to minimizing player
            bestValue = std::max(bestValue, moveValue);
        }
        return bestValue;
    }
    else
    {
        int bestValue = INT_MAX;
        for (const auto &move : board->getPossibleMoves(oppositeSign(sign)))
        {
            GameBoard tempBoard = *board;
            if (!tempBoard.move(move, oppositeSign(sign)))
                continue;
            int moveValue = minimax(&tempBoard, depth - 1, true, sign); // Decrease depth and switch to maximizing player
            bestValue = std::min(bestValue, moveValue);
        }
        return bestValue;
    }
}

Tile::Sign MinMaxAI::oppositeSign(Tile::Sign sign)
{
    return sign == Tile::X ? Tile::O : Tile::X;
}

std::vector<int> MinMaxAI::getPlay(GameBoard *board, Tile::Sign sign)
{
    std::vector<std::vector<int>> possibleMoves = board->getPossibleMoves(sign);
    std::vector<std::future<int>> futures;

    for (const auto &move : possibleMoves)
    {
        if (move.size() == 4)
        {
            //std::cout << "Move: " << move[0] << ", " << move[1] << " -> " << move[2] << ", " << move[3] << std::endl;
            // Async launch of lambda
            futures.push_back(std::async(std::launch::async, [&]()
                                         {
                                         GameBoard tempBoard = *board;
                                         if(!tempBoard.move(move, sign)) {return 0;}
                                         return minimax(&tempBoard, depth, false, sign); }));
        }
    }
    int bestValue = INT_MIN;
    std::vector<int> bestMove;

    for (size_t i = 0; i < futures.size(); ++i)
    {
        int moveValue = futures[i].get(); // Wait for all Lambda
        if (moveValue > bestValue)
        {
            bestValue = moveValue;
            bestMove = possibleMoves[i];
        }
    }
    std::cout << "bestMove: " << bestMove[0] << ", " << bestMove[1] << " -> " << bestMove[2] << ", " << bestMove[3] << std::endl;
    return bestMove;
}
