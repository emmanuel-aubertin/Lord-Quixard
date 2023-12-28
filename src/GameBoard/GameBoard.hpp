#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <iostream>
#include "./../Tile.cpp"

class GameBoard
{
public:
    GameBoard();
    bool move(const int x, const int y, const int new_x, const int new_y, const Tile::Sign sign);
    bool move(const std::vector<int>&, const Tile::Sign sign);
    void printBoard();
    std::array<std::array<Tile, 5>, 5> getBoard();
    std::vector<std::vector<int>> getPossibleMoves(const Tile::Sign currentPlayer);

private:
    bool isValidMove(const int x, const int y, const int new_x, const int new_y, const Tile::Sign sign);
    std::array<std::array<Tile, 5>, 5> board;
};
#endif