#include "PokerHands.hpp"
#include <algorithm>

int PokerHands::compare(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    HandRank l_rank1 = calcRank(p_hand1);
    HandRank l_rank2 = calcRank(p_hand2);

    if(l_rank1 != l_rank2)
    {
        return l_rank1 > l_rank2 ? 1 : -1;
    }

    if(l_rank1 == HAND_RANK_STRAIGHT_FLUSH)
    {
        return compareStraightFlush(p_hand1, p_hand2);
    }

    if(l_rank1 == HAND_RANK_FOUR_KIND)
    {
        return compareFourKind(p_hand1, p_hand2);
    }

    if(l_rank1 == HAND_RANK_FULL_HOUSE)
    {
        return compareFullHouse(p_hand1, p_hand2);
    }

    if(l_rank1 == HAND_RANK_FLUSH)
    {
        return compareFlush(p_hand1, p_hand2);
    }

    if(l_rank1 == HAND_RANK_STRAIGHT)
    {
        return compareStraight(p_hand1, p_hand2);
    }

    if(l_rank1 == HAND_RANK_THREE_KIND)
    {
        return compareThreeKind(p_hand1, p_hand2);
    }

    if(l_rank1 == HAND_RANK_TWO_PAIRS)
    {
        return compareTwoPairs(p_hand1, p_hand2);
    }

    if(l_rank1 == HAND_RANK_ONE_PAIR)
    {
        return compareOnePair(p_hand1, p_hand2);
    }

    if(l_rank1 == HAND_RANK_HIGH_CARD)
    {
        return compareHighCard(p_hand1, p_hand2);
    }

    return 0;
}

int PokerHands::compareHighCard(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    auto l_comparer = [](Card p_card1, Card p_card2){return p_card1.value() < p_card2.value();};

    return std::lexicographical_compare(p_hand1.begin(), p_hand1.end(), p_hand2.begin(), p_hand2.end(),
                                        l_comparer) ? -1 : 1;
}

int PokerHands::compareOnePair(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    int l_valueOfPair1 = getValuesOfPairs(p_hand1).front();
    int l_valueOfPair2 = getValuesOfPairs(p_hand2).front();
    if(l_valueOfPair1 != l_valueOfPair2)
    {
        return l_valueOfPair1 > l_valueOfPair2 ? 1 : -1;
    }
    else
    {
        std::vector<Card> l_handWithoutPair1, l_handWithoutPair2;
        std::copy_if(p_hand1.begin(), p_hand1.end(), std::back_inserter(l_handWithoutPair1),
                     [=](auto p_card){return p_card.value() != l_valueOfPair1;});
        std::copy_if(p_hand2.begin(), p_hand2.end(), std::back_inserter(l_handWithoutPair2),
                     [=](auto p_card){return p_card.value() != l_valueOfPair2;});

        return compareHighCard(l_handWithoutPair1, l_handWithoutPair2);
    }
}

int PokerHands::compareTwoPairs(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    std::vector<int> l_valuesOfPair1 = getValuesOfPairs(p_hand1);
    std::vector<int> l_valuesOfPair2 = getValuesOfPairs(p_hand2);

    if(not std::equal(l_valuesOfPair1.begin(), l_valuesOfPair1.end(), l_valuesOfPair2.begin()))
    {
        return std::lexicographical_compare(l_valuesOfPair1.begin(), l_valuesOfPair1.end(),
                                            l_valuesOfPair2.begin(), l_valuesOfPair2.end()) ? -1 : 1;
    }
    else
    {
        struct
        {
            bool operator()(int p_value, std::vector<int>& p_values)
            {
                return p_values.end() != std::find(p_values.begin(), p_values.end(), p_value);
            }
        }l_contains;
        auto l_highCard1 = std::find_if(p_hand1.begin(), p_hand1.end(),
                                        [&](auto p_card){return not l_contains(p_card.value(), l_valuesOfPair1);});
        auto l_highCard2 = std::find_if(p_hand2.begin(), p_hand2.end(),
                                        [&](auto p_card){return not l_contains(p_card.value(), l_valuesOfPair2);});

        return l_highCard1->value() > l_highCard2->value() ? 1 : -1;
    }
}

int PokerHands::compareThreeKind(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    int l_valueOfThreeKind1 = getValueOfKinds(p_hand1, 3);
    int l_valueOfThreeKind2 = getValueOfKinds(p_hand2, 3);

    if(l_valueOfThreeKind1 != l_valueOfThreeKind2)
    {
        return l_valueOfThreeKind1 > l_valueOfThreeKind2 ? 1 : -1;
    }
    else
    {
        return compareHighCard(p_hand1, p_hand2);
    }
}

int PokerHands::compareFourKind(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    int l_valueOfFourKind1 = getValueOfKinds(p_hand1, 4);
    int l_valueOfFourKind2 = getValueOfKinds(p_hand2, 4);

    if(l_valueOfFourKind1 != l_valueOfFourKind2)
    {
        return l_valueOfFourKind1 > l_valueOfFourKind2 ? 1 : -1;
    }
    else
    {
        auto l_highCard1 = std::find_if(p_hand1.begin(), p_hand1.end(),
                                        [=](auto p_card){return p_card.value() != l_valueOfFourKind1;});
        auto l_highCard2 = std::find_if(p_hand2.begin(), p_hand2.end(),
                                        [=](auto p_card){return p_card.value() != l_valueOfFourKind2;});

        return l_highCard1->value() > l_highCard2->value() ? 1 : -1;
    }
}

int PokerHands::compareStraight(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    return compareHighCard(p_hand1, p_hand2);
}

int PokerHands::compareStraightFlush(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    return compareHighCard(p_hand1, p_hand2);
}

int PokerHands::compareFlush(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    return compareHighCard(p_hand1, p_hand2);
}

int PokerHands::compareFullHouse(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    int l_valueOfThreeKind1 = getValueOfKinds(p_hand1, 3);
    int l_valueOfThreeKind2 = getValueOfKinds(p_hand2, 3);

    if(l_valueOfThreeKind1 != l_valueOfThreeKind2)
    {
        return l_valueOfThreeKind1 > l_valueOfThreeKind2 ? 1 : -1;
    }
    else
    {
        return compareOnePair(p_hand1, p_hand2);
    }
}

int PokerHands::getValueOfKinds(std::vector<Card> p_hand, int p_count)
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

bool PokerHands::isThreeOrFourKind(std::vector<Card> p_hand, int& p_count)
{
    p_count = 0;
    auto l_card = p_hand.begin();
    while(2 < std::distance(l_card, p_hand.end()))
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

bool PokerHands::isStraight(std::vector<Card> p_hand)
{
    for(int l_index = 1; l_index < p_hand.size(); l_index ++)
    {
        if(1 != p_hand[l_index].value() - p_hand[l_index - 1].value())
        {
            return false;
        }
    }

    return true;
}

bool PokerHands::isFlush(std::vector<Card> p_hand)
{
    char l_suit = p_hand[0].suit();

    return std::all_of(p_hand.begin(), p_hand.end(), [=](auto p_card){return p_card.suit() == l_suit;});
}

void PokerHands::sortHand(std::vector<Card> p_hand)
{
    auto l_comparer = [](Card p_card1, Card p_card2){return p_card1.value() < p_card2.value();};
    std::sort(p_hand.begin(), p_hand.end(), l_comparer);
}

HandRank PokerHands::calcRankOnFlushAndStraight(bool p_isFlush, bool p_isStraight, int p_firstValue)
{
    if(p_isFlush && p_isStraight)
    {
        if(0 == p_firstValue)
        {
            return HAND_RANK_ROYAL_FLUSH;
        }
        else
        {
            return HAND_RANK_STRAIGHT_FLUSH;
        }
    }
    else if(p_isFlush)
    {
        return HAND_RANK_FLUSH;
    }
    else
    {
        return HAND_RANK_STRAIGHT;
    }
}

HandRank PokerHands::calcRank(std::vector<Card> p_hand)
{
    sortHand(p_hand);

    bool l_isFlush = isFlush(p_hand);
    bool l_isStraight = isStraight(p_hand);

    if(l_isFlush or l_isStraight)
    {
        return calcRankOnFlushAndStraight(l_isFlush, l_isStraight, p_hand[0].value());
    }

    int l_count = 0;
    bool isKind = isThreeOrFourKind(p_hand, l_count);
    std::vector<int> l_valuesOfPairs = getValuesOfPairs(p_hand);

    if(isKind)
    {
        if(4 == l_count)
        {
            return HAND_RANK_FOUR_KIND;
        }

        if(1 == l_valuesOfPairs.size())
        {
            return HAND_RANK_FULL_HOUSE;
        }

        return HAND_RANK_THREE_KIND;
    }

    if(2 == l_valuesOfPairs.size())
    {
        return HAND_RANK_TWO_PAIRS;
    }

    if(1 == l_valuesOfPairs.size())
    {
        return HAND_RANK_ONE_PAIR;
    }

    return HAND_RANK_HIGH_CARD;
}

std::vector<int> PokerHands::getValuesOfPairs(std::vector<Card> p_hand)
{
    std::vector<int> l_valuesOfPairs;
    for(auto l_iter = p_hand.begin(); l_iter != p_hand.end(); l_iter ++)
    {
        if(2 == std::count_if(p_hand.begin(), p_hand.end(),
                              [&](Card p_card){return p_card.value() == l_iter->value();}))
        {
            if(l_valuesOfPairs.end() == std::find(l_valuesOfPairs.begin(), l_valuesOfPairs.end(), l_iter->value()))
            {
                l_valuesOfPairs.push_back(l_iter->value());
            }
        }
    }

    return l_valuesOfPairs;
}


