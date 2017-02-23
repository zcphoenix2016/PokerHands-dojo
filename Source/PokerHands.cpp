#include "PokerHands.hpp"
#include <algorithm>

const PokerHands::Comparers PokerHands::s_comparers = {
                                                        {HAND_RANK_HIGH_CARD,      &PokerHands::sequential_compare},
                                                        {HAND_RANK_ONE_PAIR,       &PokerHands::compareOnePair},
                                                        {HAND_RANK_TWO_PAIRS,      &PokerHands::compareTwoPairs},
                                                        {HAND_RANK_THREE_KIND,     &PokerHands::compareThreeKind},
                                                        {HAND_RANK_STRAIGHT,       &PokerHands::sequential_compare},
                                                        {HAND_RANK_FLUSH,          &PokerHands::sequential_compare},
                                                        {HAND_RANK_FULL_HOUSE,     &PokerHands::compareFullHouse},
                                                        {HAND_RANK_FOUR_KIND,      &PokerHands::compareFourKind},
                                                        {HAND_RANK_STRAIGHT_FLUSH, &PokerHands::sequential_compare}
                                                      };

int PokerHands::compareValues(int p_lhs, int p_rhs)
{
    return p_lhs < p_rhs ? -1 : 1;
}

int PokerHands::compare(std::vector<Card>& p_hand1, std::vector<Card>& p_hand2)
{
    std::sort(p_hand1.begin(), p_hand1.end());
    std::sort(p_hand2.begin(), p_hand2.end());

    HandRank l_rank1 = calcRank(p_hand1);
    HandRank l_rank2 = calcRank(p_hand2);

    if(l_rank1 != l_rank2)
    {
        return compareValues(l_rank1, l_rank2);
    }

    return PokerHands::s_comparers.at(l_rank1)(*this, p_hand1, p_hand2);
}

int PokerHands::sequential_compare(std::vector<Card>& p_hand1, std::vector<Card>& p_hand2)
{
    return std::lexicographical_compare(p_hand1.rbegin(), p_hand1.rend(),
                                        p_hand2.rbegin(), p_hand2.rend()) ? -1 : 1;
}

int PokerHands::compareOnePair(std::vector<Card>& p_hand1, std::vector<Card>& p_hand2)
{
    int l_valueOfPair1 = getValuesOfPairs(p_hand1).front();
    int l_valueOfPair2 = getValuesOfPairs(p_hand2).front();
    if(l_valueOfPair1 != l_valueOfPair2)
    {
        return compareValues(l_valueOfPair1, l_valueOfPair2);
    }
    else
    {
        return sequential_compare(p_hand1, p_hand2); //??
    }
}

int PokerHands::compareTwoPairs(std::vector<Card>& p_hand1, std::vector<Card>& p_hand2)
{
    std::vector<int> l_valuesOfPair1 = getValuesOfPairs(p_hand1);
    std::vector<int> l_valuesOfPair2 = getValuesOfPairs(p_hand2);

    for(int l_index = l_valuesOfPair1.size() - 1; l_index >= 0 ; l_index --)
    {
        if(l_valuesOfPair1[l_index] != l_valuesOfPair2[l_index])
        {
            return compareValues(l_valuesOfPair1[l_index], l_valuesOfPair2[l_index]);
        }
    }

    return sequential_compare(p_hand1, p_hand2);
}

int PokerHands::compareThreeKind(std::vector<Card>& p_hand1, std::vector<Card>& p_hand2)
{
    int l_valueOfThreeKind1 = getValueOfKinds(p_hand1, 3);
    int l_valueOfThreeKind2 = getValueOfKinds(p_hand2, 3);

    if(l_valueOfThreeKind1 != l_valueOfThreeKind2)
    {
        return compareValues(l_valueOfThreeKind1, l_valueOfThreeKind2);
    }
    else
    {
        return sequential_compare(p_hand1, p_hand2);
    }
}

int PokerHands::compareFourKind(std::vector<Card>& p_hand1, std::vector<Card>& p_hand2)
{
    int l_valueOfFourKind1 = getValueOfKinds(p_hand1, 4);
    int l_valueOfFourKind2 = getValueOfKinds(p_hand2, 4);

    if(l_valueOfFourKind1 != l_valueOfFourKind2)
    {
        return compareValues(l_valueOfFourKind1, l_valueOfFourKind2);
    }
    else
    {
        auto l_highCard1 = std::find_if(p_hand1.begin(), p_hand1.end(),
                                        [=](auto p_card){return p_card.value() != l_valueOfFourKind1;});
        auto l_highCard2 = std::find_if(p_hand2.begin(), p_hand2.end(),
                                        [=](auto p_card){return p_card.value() != l_valueOfFourKind2;});

        return compareValues(l_highCard1->value(), l_highCard2->value());
    }
}

int PokerHands::compareFullHouse(std::vector<Card>& p_hand1, std::vector<Card>& p_hand2)
{
    int l_valueOfThreeKind1 = getValueOfKinds(p_hand1, 3);
    int l_valueOfThreeKind2 = getValueOfKinds(p_hand2, 3);

    if(l_valueOfThreeKind1 != l_valueOfThreeKind2)
    {
        return compareValues(l_valueOfThreeKind1, l_valueOfThreeKind2);
    }
    else
    {
        return compareOnePair(p_hand1, p_hand2);
    }
}

int PokerHands::getValueOfKinds(std::vector<Card>& p_hand, int p_count)
{
    int l_valueOfKind = 0;
    auto l_card = p_hand.begin();
    while(l_card != p_hand.end())
    {
        if(p_count == std::count_if(p_hand.begin(), p_hand.end(),
                                    [&](auto p_card){return p_card.value() == l_card->value();}))
        {
            l_valueOfKind = l_card->value();
            break;
        }
        l_card ++;
    }

    return l_valueOfKind;
}

bool PokerHands::isThreeOrFourKind(std::vector<Card>& p_hand, int& p_count)
{
    p_count = 0;
    auto l_card = p_hand.begin();
    while(3 <= std::distance(l_card, p_hand.end()))
    {
        p_count = std::count_if(p_hand.begin(), p_hand.end(),
                                [&](auto p_card){return p_card.value() == l_card->value();});
        if(3 == p_count or 4 == p_count)
        {
            return true;
        }
        l_card ++;
    }

    return false;
}

bool PokerHands::isStraight(std::vector<Card>& p_hand)
{
    auto l_predicate = [](Card p_card1, Card p_card2){return 1 != p_card2.value() - p_card1.value();};
    return p_hand.end() == std::adjacent_find(p_hand.begin(), p_hand.end(), l_predicate);
}

bool PokerHands::isFlush(std::vector<Card>& p_hand)
{
    char l_suit = p_hand[0].suit();
    return std::all_of(p_hand.begin(), p_hand.end(), [=](auto p_card){return p_card.suit() == l_suit;});
}

HandRank PokerHands::calcRankForFlushOrStraight(bool p_isFlush, bool p_isStraight, int p_firstValue)
{
    if(p_isFlush && p_isStraight)
    {
        return (10 == p_firstValue) ? HAND_RANK_ROYAL_FLUSH : HAND_RANK_STRAIGHT_FLUSH;
    }
    else
    {
        return p_isFlush ? HAND_RANK_FLUSH : HAND_RANK_STRAIGHT;
    }
}

HandRank PokerHands::calcRankForKindOrFullHouse(int p_numOfKind, int p_numOfPairs)
{
    if(4 == p_numOfKind)
    {
        return HAND_RANK_FOUR_KIND;
    }

    if(1 == p_numOfPairs)
    {
        return HAND_RANK_FULL_HOUSE;
    }

    return HAND_RANK_THREE_KIND;
}

HandRank PokerHands::calcRankForPairOrHighCard(int p_numOfPairs)
{
    std::map<int, HandRank> l_ranks{{0, HAND_RANK_HIGH_CARD}, {1, HAND_RANK_ONE_PAIR}, {2, HAND_RANK_TWO_PAIRS}};
    return l_ranks[p_numOfPairs];
}

HandRank PokerHands::calcRank(std::vector<Card>& p_hand)
{
    bool l_isFlush = isFlush(p_hand);
    bool l_isStraight = isStraight(p_hand);

    if(l_isFlush or l_isStraight)
    {
        return calcRankForFlushOrStraight(l_isFlush, l_isStraight, p_hand[0].value());
    }

    int l_count = 0;
    bool isKind = isThreeOrFourKind(p_hand, l_count);
    std::vector<int> l_valuesOfPairs = getValuesOfPairs(p_hand);

    if(isKind)
    {
        return calcRankForKindOrFullHouse(l_count, l_valuesOfPairs.size());
    }

    return calcRankForPairOrHighCard(l_valuesOfPairs.size());
}

std::vector<int> PokerHands::getValuesOfPairs(std::vector<Card>& p_hand)
{
    std::vector<int> l_valuesOfPairs;
    auto l_start = p_hand.begin(), l_diff = p_hand.begin();
    while(l_diff != p_hand.end())
    {
        l_diff = std::find_if(l_start, p_hand.end(), [&](Card p_card)
                                                     {return p_card.value() != l_start->value();});
        if(2 == std::distance(l_start, l_diff))
        {
            l_valuesOfPairs.push_back(l_start->value());
        }
        l_start = l_diff;
    }

    return l_valuesOfPairs;
}


