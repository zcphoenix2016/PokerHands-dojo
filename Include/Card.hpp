#pragma once

#include <string>
#include <map>

class Card
{
public:
    Card(const std::string&);
    int value() const {return m_value;}
    char suit() const {return m_suit;}
    bool operator < (const Card&);

private:
    int m_value;
    char m_suit;
    static std::map<char, int> m_values;
};