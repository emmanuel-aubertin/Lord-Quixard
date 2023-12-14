#include <iostream>
#include "../GameBoard/GameBoard.hpp"

class GameEngine
{
public:
    GameEngine();
    bool move(const int x, const int y, const int new_x, const int new_y);
    void printBoard();

private:
    GameBoard* board;

    bool isValidMove(const int x, const int y, const int new_x, const int new_y);
};