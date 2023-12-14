#include <iostream>
#include "GameEngine.hpp"

GameEngine::GameEngine()
{
    this->board = new GameBoard();
}

bool GameEngine::move(const int x, const int y, const int new_x, const int new_y)
{
    if (!this->isValidMove(x, y, new_x, new_y))
    {
        return false;
    }
    this->board->move(x, y, new_x, new_y);
    return true;
}

void GameEngine::printBoard()
{
    this->board->printBoard();
}

/**
 * @brief Know if a move is legal or not
 *
 * @param x
 * @param y
 * @param new_x
 * @param new_y
 * @return true if the move is legal
 * @return false if the move isn't legal
 */
bool GameEngine::isValidMove(const int x, const int y, const int new_x, const int new_y)
{
    // As already a sign
    if (this->board->getBoard()[x][y].sign != Tile::Blank)
    {
        return false;
    }

    // If out of board
    if (x > 4 || y > 4 || new_x == x && new_y == y)
    {
        return false;
    }

    // If not an extern cell
    if (x != 0 && x != 4 && y != 0 && y != 4)
    {
        return false;
    }

    // If not an extern cell
    if (new_x != 0 && new_x != 4 && new_y != 0 && new_y != 4)
    {
        return false;
    }

    // If not placed on the same x or y
    if (new_x != x && new_y != y)
    {
        return false;
    }

    return true;
}