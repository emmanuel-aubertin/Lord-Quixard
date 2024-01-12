#include "./PlayerAI.hpp"

/**
 * @brief Construct a new PlayerAI object.
 * Initializes the AI player with the given name and outputs a creation message to the console.
 * This constructor is also intended for initializing any future AI-specific features.
 *
 * @param name The name of the AI player.
 */
PlayerAI::PlayerAI(const std::string &name) : Player(name)
{
    std::cout << "Create " << name << " player (AI)" << std::endl;
    // Here for a future feature :)
}

/**
 * @brief Determines the AI player's move.
 * Currently, this method returns an empty vector, indicating no move is made.
 * This method is meant to be expanded in the future to calculate and return the AI's move based on the game board state and the AI player's sign.
 *
 * @param gameBoard Pointer to the current game board.
 * @param sign The AI player's sign (X or O).
 * @return std::vector<int> The AI player's chosen move, represented as a vector. Currently returns an empty vector.
 */
std::vector<int> PlayerAI::getPlay(GameBoard *, Tile::Sign)
{
    return std::vector<int>();
}