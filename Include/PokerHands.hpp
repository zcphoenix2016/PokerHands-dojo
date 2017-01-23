#pragma once

#include <vector>
#include "Card.hpp"

enum HandRank
{
    HAND_RANK_HIGH_CARD = 0,
    HAND_RANK_ONE_PAIR,
    HAND_RANK_TWO_PAIRS
};

const int INVALID_VALUE = -1;

class PokerHands
{
public:
    int compare(std::vector<Card>, std::vector<Card>);
private:
    bool isOnePair(std::vector<Card>);
    bool isTwoPairs(std::vector<Card>);
    HandRank calcRank(std::vector<Card>);
    int findHighestVal(std::vector<Card>);
    int getThePairValueFromOnePair(std::vector<Card>);
};
