#include "MinMaxAI.hpp"
#include "../../../GameBoard/GameBoard.hpp"
#include <thread>
#include <future>
#include <algorithm>

/**
 * @brief Construct a new MinMaxAI object with default depth.
 * Initializes the MinMaxAI player with the given name and sets the depth of the Minimax algorithm to a default value.
 *
 * @param name The name of the MinMaxAI player.
 */
MinMaxAI::MinMaxAI(const std::string &name) : PlayerAI(name)
{
    depth = 3;
}

/**
 * @brief Construct a new MinMaxAI object with specified depth.
 * Initializes the MinMaxAI player with the given name and sets the depth of the Minimax algorithm to the specified value.
 *
 * @param name The name of the MinMaxAI player.
 * @param depth The depth for the Minimax algorithm.
 */
MinMaxAI::MinMaxAI(const std::string &name, int depth) : PlayerAI(name)
{
    this->depth = depth;
}

/**
 * @brief Destructor for the MinMaxAI object.
 * Cleans up resources, if necessary, when the MinMaxAI object is destroyed.
 */
MinMaxAI::~MinMaxAI()
{
    // Cleanup code, if necessary
}

/**
 * @brief Evaluates the game board from the perspective of the given sign.
 * Calculates a score for the board based on the current state, favoring positions beneficial to the specified sign.
 *
 * @param board Pointer to the current game board.
 * @param sign The player's sign (X or O) for whom the board is being evaluated.
 * @return int The evaluation score of the board.
 */
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

/**
 * @brief Evaluates a line (row, column, or diagonal) on the board.
 * Counts the number of tiles matching the given sign and those of the opponent, calculating a score based on these counts.
 *
 * @param board The current game board.
 * @param xStart Starting x-coordinate for evaluation.
 * @param yStart Starting y-coordinate for evaluation.
 * @param xStep Step size in the x-direction.
 * @param yStep Step size in the y-direction.
 * @param sign The player's sign (X or O) to evaluate for.
 * @return int The evaluation score of the line.
 */
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

/**
 * @brief The Minimax algorithm implementation.
 * Recursively evaluates game board states to determine the optimal move for the AI.
 * Alternates between maximizing and minimizing players based on the current depth.
 *
 * @param board Pointer to the current game board.
 * @param depth Current depth in the Minimax algorithm.
 * @param isMaximizingPlayer Boolean indicating if the current player is maximizing.
 * @param sign The player's sign (X or O) for the current turn.
 * @return int The best evaluated score for the current player at this depth.
 */
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

/**
 * @brief Returns the opposite sign of the given player's sign.
 * Useful for switching between players in the Minimax algorithm.
 *
 * @param sign The current player's sign (X or O).
 * @return Tile::Sign The opposite sign of the given sign.
 */
Tile::Sign MinMaxAI::oppositeSign(Tile::Sign sign)
{
    return sign == Tile::X ? Tile::O : Tile::X;
}

/**
 * @brief Determines the best play for the AI using the Minimax algorithm.
 * Evaluates all possible moves using the Minimax algorithm asynchronously and selects the move with the best score.
 *
 * @param board Pointer to the current game board.
 * @param sign The AI player's sign (X or O).
 * @return std::vector<int> The AI player's best move, represented as a vector {x, y, new_x, new_y}.
 */
std::vector<int> MinMaxAI::getPlay(GameBoard *board, Tile::Sign sign)
{
    std::vector<std::vector<int>> possibleMoves = board->getPossibleMoves(sign);
    std::vector<std::future<int>> futures;

    for (const auto &move : possibleMoves)
    {
        if (move.size() == 4)
        {
            // std::cout << "Move: " << move[0] << ", " << move[1] << " -> " << move[2] << ", " << move[3] << std::endl;
            //  Async launch of lambda
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
