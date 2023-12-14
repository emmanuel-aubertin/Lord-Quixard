#include <iostream>
#include "GameEngine.hpp"
#include "../Player/AIPlayer/PlayerAI.hpp"

GameEngine::GameEngine(Player &playerOne, Player &playerTwo)
    : playerOne(playerOne), playerTwo(playerTwo)
{
    this->board = new GameBoard();
    this->playerOne = playerOne;
    this->playerTwo = playerTwo;
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

bool GameEngine::isWinner() {
    for (int i = 0; i < this->board->getBoard().size(); ++i) {
        if (isRowWin(i) || isColumnWin(i)) {
            return true;
        }
    }
    return isMainDiagonalWin() || isAntiDiagonalWin();
}

bool GameEngine::isRowWin(int row) {
    const auto& firstSign = this->board->getBoard()[row][0].sign;
    if (firstSign == Tile::Blank) return false;

    for (int j = 1; j < this->board->getBoard().size(); ++j) {
        if (this->board->getBoard()[row][j].sign != firstSign) return false;
    }
    return true;
}

bool GameEngine::isColumnWin(int column) {
    const auto& firstSign = this->board->getBoard()[0][column].sign;
    if (firstSign == Tile::Blank) return false;

    for (int i = 1; i < this->board->getBoard().size(); ++i) {
        if (this->board->getBoard()[i][column].sign != firstSign) return false;
    }
    return true;
}

bool GameEngine::isMainDiagonalWin() {
    const auto& firstSign = this->board->getBoard()[0][0].sign;
    if (firstSign == Tile::Blank) return false;

    for (int i = 1; i < this->board->getBoard().size(); ++i) {
        if (this->board->getBoard()[i][i].sign != firstSign) return false;
    }
    return true;
}

bool GameEngine::isAntiDiagonalWin() {
    const auto& firstSign = this->board->getBoard()[0][this->board->getBoard().size() - 1].sign;
    if (firstSign == Tile::Blank) return false;

    for (int i = 1; i < this->board->getBoard().size(); ++i) {
        if (this->board->getBoard()[i][this->board->getBoard().size() - i - 1].sign != firstSign) return false;
    }
    return true;
}

void GameEngine::makeIAmove()
{
    PlayerAI *aiPlayer = dynamic_cast<PlayerAI *>(&playerTwo);
    if (aiPlayer != nullptr)
    {
        std::vector<int> play = aiPlayer->getPlay(this->board);
        while (!this->move(play[0], play[1], play[2], play[3]))
        {
            play = aiPlayer->getPlay(this->board);
        }
    }
    else
    {
        std::cerr << "Error: playerTwo is not an AI player." << std::endl;
    }
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