#pragma once

#include <string>
#include <map>

class Card
{
public:
    Card(const std::string&);
    int value(){return m_value;}
    char suit(){return m_suit;}

private:
    int m_value;
    char m_suit;
    static std::map<char, int> m_values;
};