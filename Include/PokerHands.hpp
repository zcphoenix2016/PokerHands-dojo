#pragma once

#include <vector>
#include "Card.hpp"

enum HandRank
{
    HAND_RANK_HIGH_CARD = 0,
    HAND_RANK_ONE_PAIR,
    HAND_RANK_TWO_PAIRS,
    HAND_RANK_THREE_KIND,
    HAND_RANK_STRAIGHT,
    HAND_RANK_FLUSH,
    HAND_RANK_FULL_HOUSE,
    HAND_RANK_FOUR_KIND
};

const int INVALID_VALUE = -1;

class PokerHands
{
public:
    int compare(std::vector<Card>, std::vector<Card>);
private:
    std::vector<int> valuesOfPairs(std::vector<Card>);
    bool             isThreeKind(std::vector<Card>);
    bool             isStraight(std::vector<Card>);
    bool             isFlush(std::vector<Card>);
    bool             isFullHouse(std::vector<Card>);
    bool             isFourKind(std::vector<Card>);
    HandRank         calcRank(std::vector<Card>);
    int              getValueOfKinds(std::vector<Card>, int);
    int              compareHighCard(std::vector<Card>, std::vector<Card>);
    int              compareOnePair(std::vector<Card>, std::vector<Card>);
    int              compareTwoPairs(std::vector<Card>, std::vector<Card>);
    int              compareThreeKind(std::vector<Card>, std::vector<Card>);
    int              compareStraight(std::vector<Card>, std::vector<Card>);
    int              compareFlush(std::vector<Card>, std::vector<Card>);
    int              compareFullHouse(std::vector<Card>, std::vector<Card>);
    int              compareFourKind(std::vector<Card>, std::vector<Card>);
};
