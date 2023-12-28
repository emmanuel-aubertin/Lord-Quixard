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

std::vector<std::vector<int>> GameBoard::getPossibleMoves(const Tile::Sign currentPlayer)
{
    std::vector<std::vector<int>> moves;

    // Iterate over the edges of the board
    for (int i = 0; i < 5; ++i)
    {
        // Top row and bottom row
        for (int row : {0, 4})
        {
            if (board[row][i].sign == Tile::Blank || board[row][i].sign == currentPlayer)
            {
                // Add all possible moves for this piece
                for (int newRow : {0, 4})
                {
                    if (newRow != row)
                    {
                        if (isValidMove(row, i, newRow, i, currentPlayer))
                        {
                            moves.push_back({row, i, newRow, i}); // {x, y, new_x, new_y}
                        }
                    }
                }
            }
        }

        // Left column and right column
        for (int col : {0, 4})
        {
            if (board[i][col].sign == Tile::Blank || board[i][col].sign == currentPlayer)
            {
                // Add all possible moves for this piece
                for (int newCol : {0, 4})
                {
                    if (newCol != col)
                    {
                        if (isValidMove(i, col, i, newCol, currentPlayer))
                        {
                            moves.push_back({i, col, i, newCol}); // {x, y, new_x, new_y}
                        }
                    }
                }
            }
        }
    }

    return moves;
}

bool GameBoard::move(const std::vector<int> &inMove, const Tile::Sign sign)
{
    if (inMove.size() != 4)
    {
        std::cout << "Vector Size not Valid" << std::endl;
        return false; // Invalid move vector
    }
    return move(inMove[0], inMove[1], inMove[2], inMove[3], sign);
}

bool GameBoard::move(const int x, const int y, const int new_x, const int new_y, const Tile::Sign sign)
{
    // Check if the move is valid
    if (!isValidMove(x, y, new_x, new_y, sign))
    {
        return false;
    }

    // If the move is along the same row
    if (y == new_y)
    {
        if (x < new_x)
        { // Moving to the right
            for (int i = x; i < new_x; ++i)
            {
                board[y][i] = board[y][i + 1];
            }
        }
        else
        { // Moving to the left
            for (int i = x; i > new_x; --i)
            {
                board[y][i] = board[y][i - 1];
            }
        }
    }

    // If the move is along the same column
    else if (x == new_x)
    {
        if (y < new_y)
        { // Moving down
            for (int i = y; i < new_y; ++i)
            {
                board[i][x] = board[i + 1][x];
            }
        }
        else
        { // Moving up
            for (int i = y; i > new_y; --i)
            {
                board[i][x] = board[i - 1][x];
            }
        }
    }

    board[new_y][new_x].sign = sign;

    return true;
}

bool GameBoard::isValidMove(const int x, const int y, const int new_x, const int new_y, const Tile::Sign sign)
{
    if (x != 0 && x != 5 - 1 && y != 0 && y != 5 - 1)
    {
        std::cout << "Not an edge tile" << std::endl;
        return false; // Not an edge tile
    }

    if (board[y][x].sign != Tile::Blank && board[y][x].sign != sign)
    {
        /*std::cout << "Tile not blank or not player's sign" << std::endl;
        this->printBoard();*/
        return false; // Tile not blank or not player's sign
    }

    if (x != new_x && y != new_y)
    {
        std::cout << "Not on same row and col" << std::endl;
        return false; // Not on same row and col
    }

    return true;
}

std::array<std::array<Tile, 5>, 5> GameBoard::getBoard()
{
    return this->board;
}