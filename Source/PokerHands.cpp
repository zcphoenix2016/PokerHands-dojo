#include "PokerHands.hpp"
#include <map>

map<char, int> g_map 
{
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 9},
    {'T', 10},
    {'J', 11},
    {'Q', 12},
    {'K', 13},
    {'A', 14}
};

Card::Card(string p_cardVal)
{
    m_value = g_map[p_cardVal[0]];
    m_suit = p_cardVal[1];
}

int compare(vector<Card> cards1, vector<Card> card2)
{
    return -1;
}
