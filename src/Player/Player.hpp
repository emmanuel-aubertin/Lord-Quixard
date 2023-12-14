#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>

class Player
{
public:
    explicit Player(const std::string &name);
    virtual ~Player() = default;
    std::string getName();

protected:
    void setName(const std::string &name);
    std::string name;
};
#endif 