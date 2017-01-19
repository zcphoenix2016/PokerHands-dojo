#pragma once

#include <string>
#include <vector>

using namespace std;

class Card
{
public:
    Card(string p_cardVal);
    
    int m_value;
    char m_suit;   
};


int compare(vector<Card> cards1, vector<Card> card2);
