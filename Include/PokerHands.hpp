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
    Card(const string&);
    
    int m_value;
    char m_suit;   
};

class PokerHands
{
public:
     int compare(vector<Card>, vector<Card>);
private:
     bool isOnePair(vector<Card>);
     bool isTwoPairs(vector<Card>);
     CardsRank calcRank(vector<Card>);
     int findHighestVal(vector<Card>);
     int getThePairValueFromOnePair(vector<Card>);
};
