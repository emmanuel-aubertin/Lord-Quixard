#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <iostream>
#include "./../Tile.cpp"
#include <array>
#include <vector>

class GameBoardMemento
{
private:
    std::array<std::array<Tile, 5>, 5> boardState;

public:
    GameBoardMemento(const std::array<std::array<Tile, 5>, 5> &state) : boardState(state) {}

    std::array<std::array<Tile, 5>, 5> getState() const
    {
        return boardState;
    }
};

class GameBoard
{
public:
    GameBoard();
    bool move(const int x, const int y, const int new_x, const int new_y, const Tile::Sign sign);
    bool move(const std::vector<int> &, const Tile::Sign sign);
    void printBoard();
    std::array<std::array<Tile, 5>, 5> getBoard();
    std::vector<std::vector<int>> getPossibleMoves(const Tile::Sign currentPlayer);

    GameBoardMemento saveToMemento()
    {
        return GameBoardMemento(board);
    }

    void restoreFromMemento(const GameBoardMemento memento)
    {
        board = memento.getState();
    }

private:
    bool isValidMove(const int x, const int y, const int new_x, const int new_y, const Tile::Sign sign);
    std::array<std::array<Tile, 5>, 5> board;
};


#endif