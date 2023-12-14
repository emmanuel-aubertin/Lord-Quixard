#include "PlayerHuman.hpp"

PlayerHuman::PlayerHuman(const std::string &name) : Player(name)
{
    std::cout << "Create "<< name <<" player (Human)" << std::endl;
    // Here for a future feature :)
}