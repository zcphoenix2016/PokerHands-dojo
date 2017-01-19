#pragma once

#include <string>
#include <vector>

using namespace std;

class Card
{
public:
    explicit Card(const string& p_cardVal);
    
    int m_value;
    char m_suit;   
};

class PokerHands
{
public:
     static int compare(vector<Card> p_cards1, vector<Card> p_card2);
private:
     static bool isOnePair(vector<Card> p_cards);
     static bool isTwoPairs(vector<Card> p_cards);
};
