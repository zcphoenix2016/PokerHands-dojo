#include "Card.hpp"
#include <cctype>

std::map<char, int> Card::m_values{{'2', 2},
                                   {'3', 3},
                                   {'4', 4},
                                   {'5', 5},
                                   {'6', 6},
                                   {'7', 7},
                                   {'8', 8},
                                   {'9', 9},
                                   {'T', 10},
                                   {'J', 11},
                                   {'Q', 12},
                                   {'K', 13},
                                   {'A', 14}};

Card::Card(const std::string& p_str)
{
    m_value = Card::m_values[p_str[0]];
    m_suit = std::toupper(p_str[1]);
}

bool Card::operator < (const Card& p_rhs)
{
    return m_value < p_rhs.value();
}