#pragma once

#include <string>
#include "PokerHands.hpp"

class Context
{
public:
    int handleFile(const std::string&);

private:
    PokerHands m_pokerHands;
};
