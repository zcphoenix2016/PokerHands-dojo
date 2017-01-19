#pragma once

#include <string>
#include <vector>

using namespace std;

enum CardsRank
{
    CARDS_RANK_HIGH_CARD = 0,
    CARDS_RANK_ONE_PAIR,
    CARDS_RANK_TWO_PAIRS
};

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
     static CardsRank calcRank(vector<Card> p_cards);
     static int findHighestVal(vector<Card> p_cards);
     static int getThePairValueFromOnePair(vector<Card> p_cards);
};
