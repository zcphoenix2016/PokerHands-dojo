#include "PokerHands.hpp"
#include <algorithm>

int PokerHands::compare(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    HandRank l_rank1 = calcRank(p_hand1);
    HandRank l_rank2 = calcRank(p_hand2);

    if(l_rank1 == l_rank2)
    {
        if(l_rank1 == HAND_RANK_ONE_PAIR)
        {
            return compareOnePair(p_hand1, p_hand2);
        }

        if(l_rank1 == HAND_RANK_HIGH_CARD)
        {
            return compareHighCard(p_hand1, p_hand2);
        }
    }

    return l_rank1 > l_rank2 ? 1 : -1;
}

int PokerHands::compareHighCard(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    return findHighestValue(p_hand1) > findHighestValue(p_hand2) ? 1 : -1;
}

int PokerHands::compareOnePair(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    int l_valueOfPair1 = valuesOfPairs(p_hand1).front();
    int l_valueOfPair2 = valuesOfPairs(p_hand2).front();
    if (l_valueOfPair1 == l_valueOfPair2)
    {
        std::vector<Card> l_handWithoutPair1, l_handWithoutPair2;
        for(auto l_card : p_hand1)
        {
            if(l_card.value() != l_valueOfPair1)
            {
                l_handWithoutPair1.push_back(l_card);
            }
        }
        for(auto l_card : p_hand2)
        {
            if(l_card.value() != l_valueOfPair2)
            {
                l_handWithoutPair2.push_back(l_card);
            }
        }
        return findHighestValue(l_handWithoutPair1) > findHighestValue(l_handWithoutPair2) ? 1 : -1;
    }
    else
    {
        return l_valueOfPair1 > l_valueOfPair2 ? 1 : -1;
    }
}

HandRank PokerHands::calcRank(std::vector<Card> p_hand)
{
    HandRank l_rank = HAND_RANK_HIGH_CARD;

    std::vector<int> l_valuesOfPairs = valuesOfPairs(p_hand);

    if(2 == l_valuesOfPairs.size())
    {
        l_rank = HAND_RANK_TWO_PAIRS;
    }
    else if(1 == l_valuesOfPairs.size())
    {
        l_rank = HAND_RANK_ONE_PAIR;
    }

    return l_rank;
}

std::vector<int> PokerHands::valuesOfPairs(std::vector<Card> p_hand)
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

int PokerHands::findHighestValue(std::vector<Card> p_hand)
{
    auto l_comparer = [](Card p_card1, Card p_card2){return p_card1.value() < p_card2.value();};
    auto l_maxCard = std::max_element(p_hand.begin(), p_hand.end(), l_comparer);

    return l_maxCard->value();
}


