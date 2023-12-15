#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <iostream>
#include "../GameBoard/GameBoard.hpp"
#include "../Player/Player.hpp"
#include "../Tile.cpp"

class GameEngine
{
public:
    GameEngine(Player &playerOne, Player &playerTwo);
    bool move(const int x, const int y, const int new_x, const int new_y);
    void printBoard();
    void makeIAmove();
    bool isWinner();
    bool isDraw();
private:
    GameBoard *board;
    Player &playerOne;
    Player &playerTwo;
    Tile::Sign whichPlay;

    bool isRowWin(int row);
    bool isColumnWin(int column);
    bool isMainDiagonalWin();
    bool isAntiDiagonalWin();

    void toogleWichPlay();

    bool isValidMove(const int x, const int y, const int new_x, const int new_y);
};
#endif