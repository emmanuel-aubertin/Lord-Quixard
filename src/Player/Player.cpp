#include "Player.hpp"

Player::Player(const std::string &name) : name(name)
{
    setName(name);
}

void Player::setName(const std::string &name)
{
    this->name = name;
}

std::string Player::getName()
{
    return this->name;
}