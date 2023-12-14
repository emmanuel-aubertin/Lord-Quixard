#include <iostream>
#include "./../Tile.cpp"

class GameBoard
{
public:
    GameBoard();
    bool move(const int x, const int y, const int new_x, const int new_y);
    void printBoard();
private:
    std::array<std::array<Tile, 5>, 5> board;
    
    bool isValidMove(const int x, const int y, const int new_x, const int new_y);
};