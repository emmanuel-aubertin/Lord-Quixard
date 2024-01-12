#include "Player.hpp"

/**
 * @brief Construct a new Player object.
 * Initializes the player with the provided name.
 *
 * @param name The name of the player.
 */
Player::Player(const std::string &name) : name(name)
{
    setName(name);
}

/**
 * @brief Sets the name of the player.
 * Updates the player's name to the provided string.
 *
 * @param name The new name to be set for the player.
 */
void Player::setName(const std::string &name)
{
    this->name = name;
}

/**
 * @brief Gets the name of the player.
 * Returns the current name of the player.
 *
 * @return std::string The name of the player.
 */
std::string Player::getName()
{
    return this->name;
}