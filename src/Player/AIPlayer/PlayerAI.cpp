#include "./PlayerAI.hpp"

PlayerAI::PlayerAI(const std::string &name) : Player(name)
{
    std::cout << "Create "<< name <<" player (AI)" << std::endl;
    // Here for a future feature :)
}

std::vector<int> PlayerAI::getPlay(GameBoard*, Tile::Sign) {
    return std::vector<int>();
}