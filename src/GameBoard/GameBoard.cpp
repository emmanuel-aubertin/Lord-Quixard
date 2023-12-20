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

void GameBoard::printBoard()
{
    for (const auto &row : board)
    {
        for (const auto &tile : row)
        {
            if (tile.sign == Tile::X)
            {
                std::cout << "X ";
            }
            else if (tile.sign == Tile::O)
            {
                std::cout << "O ";
            }
            else
            {
                std::cout << "B ";
            }
        }
        std::cout << std::endl;
    }
}

bool GameBoard::move(const int x, const int y, const int new_x, const int new_y, const Tile::Sign sign)
{
    bool change = board[x][y].sign == Tile::Blank;

    std::cout << "Move : From (" << x << ", " << y << " ) To (" << new_x << ", " << new_y << ")" << std::endl;
    if (sign == Tile::O)
    {
        std::cout << "O" << std::endl;
    }
    else if (sign == Tile::Blank)
    {
        std::cout << "B" << std::endl;
    }
    else if (sign == Tile::X)
    {
        std::cout << "X" << std::endl;
    }
    if (new_x == x)
    {

        if (new_y < y)
        {
            std::cout << new_y << "<" << y << std::endl;
            Tile prev = board[x][y];
            for (int i = new_y; i <= y; ++i)
            {
                Tile temp = board[x][i];
                board[x][i] = prev;
                prev = temp;
            }
            if (change)
            {
                board[new_x][new_y].sign = sign;
            }
            return true;
        }
        Tile prev = board[x][new_y];
        for (int i = new_y; i >= y; --i)
        {
            Tile temp = board[x][i];
            board[x][i] = prev;
            prev = temp;
        }
        if (change)
        {
            board[new_x][new_y].sign = sign;
        }
        return true;
    }

    if (new_x < x)
    {
        Tile prev = board[x][y];
        for (int i = new_x; i <= x; i++)
        {
            std::cout << "[" << i << "][" << y << "] = ";
            if (board[i][y].sign == Tile::O)
            {
                std::cout << "O" << std::endl;
            }
            else if (board[i][y].sign == Tile::Blank)
            {
                std::cout << "B" << std::endl;
            }
            else if (board[i][y].sign == Tile::X)
            {
                std::cout << "X" << std::endl;
            }
            Tile temp = board[i][y];
            board[i][y] = prev;
            prev = temp;
        }
        if (change)
        {
            board[new_x][new_y].sign = sign;
        }
        return true;
    }
    Tile prev = board[new_x][y];
    for (int i = new_x; i >= x; i--)
    {
        Tile temp = board[i][y];
        board[i][y] = prev;
        prev = temp;
    }
    if (change)
    {
        board[new_x][new_y].sign = sign;
    }
    return true;
}
/*std::cout << "[" << i << "][" << y  << "] = ";
if( board[i][y].sign == Tile::O) {
    std::cout << "O" << std::endl;
} else if( board[i][y].sign == Tile::Blank) {
    std::cout << "B" << std::endl;
} else if( board[i][y].sign == Tile::X) {
    std::cout << "X" << std::endl;
}*/
std::array<std::array<Tile, 5>, 5> GameBoard::getBoard()
{
    return this->board;
}