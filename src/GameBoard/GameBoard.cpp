#include "GameBoard.hpp"

/**
 * @brief Construct a new Game Board:: Game Board object
 *
 */
GameBoard::GameBoard()
{
    for (auto &row : board)
    {
        row.fill(Tile());
    }
}

void GameBoard::printBoard() {
    for (const auto& row : board) {
        for (const auto& tile : row) {
            if(tile.sign == Tile::X){
                std::cout << "X ";
            } else if(tile.sign == Tile::O){
                std::cout << "O ";
            } else {
                std::cout << "B ";
            }
            
        }
        std::cout << std::endl;
    }
}

bool GameBoard::move(const int x, const int y, const int new_x, const int new_y)
{
    if (!this->isValidMove(x, y, new_x, new_y))
    {
        return false;
    }
    
    std::cout << "Move : From ("<< x <<", "<< y <<" ) To ("<< new_x <<", "<< new_y <<")" << std::endl;
    if (new_x == x)
    {
       
        if (new_y < y)
        {
            Tile prev = board[x][y];
            for (int i = y; i <= new_y; i++)
            {
                Tile temp = board[x][i];
                board[x][i] = prev;
                prev = temp;
            }
            board[new_x][new_y].sign = Tile::X;
            return true;
        }
        Tile prev = board[x][new_y];
        for (int i = new_y; i >= y; i--)
        {
            Tile temp = board[x][i];
            board[x][i] = prev;
            prev = temp;
        }
        board[new_x][new_y].sign = Tile::X;
        return true;
    }
    
    if (new_x < x)
    {
        Tile prev = board[x][y];
        for (int i = x; i < new_x; i++)
        {
            Tile temp = board[i][y];
            board[i][y] = prev;
            prev = temp;
        }
        board[new_x][new_y].sign = Tile::X;
        return true;
    }
    Tile prev = board[new_x][y];
    for (int i = new_x; i > x; i--)
    {
        Tile temp = board[i][y];
        board[i][y] = prev;
        prev = temp;
    }
    board[new_x][new_y].sign = Tile::X;
    return true;
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
bool GameBoard::isValidMove(const int x, const int y, const int new_x, const int new_y)
{
    // As already a sign
    if (this->board[x][y].sign != Tile::Blank)
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