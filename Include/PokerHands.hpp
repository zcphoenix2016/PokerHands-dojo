#pragma once

#include <vector>
#include "Card.hpp"

enum CardsRank
{
    CARDS_RANK_HIGH_CARD = 0,
    CARDS_RANK_ONE_PAIR,
    CARDS_RANK_TWO_PAIRS
};

const int INVALID_VALUE = -1;

class PokerHands
{
public:
    int compare(std::vector<Card>, std::vector<Card>);
private:
    bool isOnePair(std::vector<Card>);
    bool isTwoPairs(std::vector<Card>);
    CardsRank calcRank(std::vector<Card>);
    int findHighestVal(std::vector<Card>);
    int getThePairValueFromOnePair(std::vector<Card>);
};
