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


int compare(vector<Card> p_cards1, vector<Card> p_card2);
bool isOnePair(vector<Card> p_cards);
