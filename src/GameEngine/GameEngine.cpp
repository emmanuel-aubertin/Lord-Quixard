#include <iostream>
#include "GameEngine.hpp"
#include "../Player/AIPlayer/PlayerAI.hpp"

GameEngine::GameEngine(Player &playerOne, Player &playerTwo)
    : playerOne(playerOne), playerTwo(playerTwo)
{
    this->board = new GameBoard();
    this->playerOne = playerOne;
    this->playerTwo = playerTwo;
    this->whichPlay = Tile::X;
    history.push_back(board->saveToMemento());
}

Player GameEngine::getWinner()
{
    if (!isWinner())
    {
        throw std::runtime_error("No winner yet"); // Or handle it some other way
    }
    if (this->whichPlay == Tile::X)
    {
        // std::cout << "WINNER: O" << std::endl;
        return playerTwo;
    }
    // std::cout << "WINNER: X" << std::endl;
    return playerOne;
}

void GameEngine::toogleWichPlay()
{
    if (this->whichPlay == Tile::X)
    {
        this->whichPlay = Tile::O;
        return;
    }
    this->whichPlay = Tile::X;
}

bool GameEngine::move(const int index, const int new_x, const int new_y)
{
    std::pair<int, int> coords = this->getCoordsFromIndex(index);
    return this->move(coords.first, coords.second, new_x, new_y);
}

bool GameEngine::move(const int x, const int y, const int new_x, const int new_y)
{
    if (!this->isValidMove(x, y, new_x, new_y))
    {
        return false;
    }
    if (this->board->move(x, y, new_x, new_y, this->whichPlay))
    {
        history.push_back(board->saveToMemento());
        this->toogleWichPlay();
        return true;
    }
    return false;
}

void GameEngine::undoMove()
{
    if (history.size() != 1)
    {
        std::cout << "History not empty" << std::endl;
        std::cout << "History size: " << history.size() << std::endl;
        history.pop_back();
        board->restoreFromMemento(history.back());
        this->toogleWichPlay();
        PlayerAI *aiPlayer = dynamic_cast<PlayerAI *>(&playerTwo);
        if (whichPlay == Tile::O && aiPlayer != nullptr)
        {
            // Undoing AI move...
            undoMove();
        }
        std::cout << "Grid updated" << std::endl;
    }
    printBoard();
}

void GameEngine::printBoard()
{
    this->board->printBoard();
}

Tile::Sign GameEngine::getWichSignPlay()
{
    return this->whichPlay;
}

std::pair<int, int> GameEngine::getCoordsFromIndex(const int index)
{
    int col = index / 5;
    int row = index % 5;
    return std::make_pair(row, col);
}

int GameEngine::getIndexFromCoords(const int x, const int y)
{
    return x * 5 + y;
}

std::array<std::array<Tile, 5>, 5> GameEngine::getBoard()
{
    return this->board->getBoard();
}

std::vector<std::pair<int, int>> GameEngine::getPlayableFrom(int x, int y)
{
    std::vector<std::pair<int, int>> output;
    const int gridSize = 5;
    // Not very opti but win of time :)
    for (int new_x = 0; new_x < gridSize; ++new_x)
    {
        for (int new_y = 0; new_y < gridSize; ++new_y)
        {
            if (isValidMove(x, y, new_x, new_y))
            {
                output.emplace_back(new_x, new_y);
            }
        }
    }
    return output;
}

bool GameEngine::isWinner()
{
    for (int i = 0; i < this->board->getBoard().size(); ++i)
    {
        if (isRowWin(i) || isColumnWin(i))
        {
            return true;
        }
    }
    return isMainDiagonalWin() || isAntiDiagonalWin();
}

bool GameEngine::isRowWin(int row)
{
    Tile::Sign firstSign = this->board->getBoard()[row][0].sign;
    if (firstSign == Tile::Blank)
        return false;

    for (int j = 1; j < this->board->getBoard().size(); ++j)
    {
        if (this->board->getBoard()[row][j].sign != firstSign)
            return false;
    }
    return true;
}

bool GameEngine::isColumnWin(int column)
{
    Tile::Sign firstSign = this->board->getBoard()[0][column].sign;
    if (firstSign == Tile::Blank)
        return false;

    for (int i = 1; i < this->board->getBoard().size(); ++i)
    {
        if (this->board->getBoard()[i][column].sign != firstSign)
            return false;
    }
    return true;
}

bool GameEngine::isMainDiagonalWin()
{
    Tile::Sign firstSign = this->board->getBoard()[0][0].sign;
    if (firstSign == Tile::Blank)
        return false;

    for (int i = 1; i < this->board->getBoard().size(); ++i)
    {
        if (this->board->getBoard()[i][i].sign != firstSign)
            return false;
    }
    return true;
}

bool GameEngine::isAntiDiagonalWin()
{
    Tile::Sign firstSign = this->board->getBoard()[0][this->board->getBoard().size() - 1].sign;
    if (firstSign == Tile::Blank)
        return false;

    for (int i = 1; i < this->board->getBoard().size(); ++i)
    {
        if (this->board->getBoard()[i][this->board->getBoard().size() - i - 1].sign != firstSign)
            return false;
    }
    return true;
}

void GameEngine::makeIAmove()
{
    PlayerAI *aiPlayer = dynamic_cast<PlayerAI *>(&playerTwo);
    if (aiPlayer != nullptr)
    {
        std::vector<int> play = aiPlayer->getPlay(this->board, this->whichPlay);
        if (this->move(play[0], play[1], play[2], play[3]))
        {
            return;
        }
        printBoard();
        makeIAmove();
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

    // If it's not a good new place
    if (x == new_x)
    {
        if (new_y != 0 && new_y != 4)
        {
            return false;
        }
    }

    if (y == new_y)
    {
        if (new_x != 0 && new_x != 4)
        {
            return false;
        }
    }

    // If not placed on the same x or y
    if (new_x != x && new_y != y)
    {
        return false;
    }

    return true;
}

Tile::Sign GameEngine::getWinnerSign()
{
    if (!isWinner())
    {
        return Tile::Blank;
    }
    for (int i = 0; i < this->board->getBoard().size(); ++i)
    {
        if (isRowWin(i))
            return this->board->getBoard()[i][0].sign;
        if (isColumnWin(i))
            return this->board->getBoard()[0][i].sign;
    }
    if (isMainDiagonalWin())
        return this->board->getBoard()[0][0].sign;
    if (isAntiDiagonalWin())
        return this->board->getBoard()[0][this->board->getBoard().size() - 1].sign;
    return Tile::Blank;
}
