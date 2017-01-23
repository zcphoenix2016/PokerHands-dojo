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
            auto l_val1 = getThePairValueFromOnePair(p_hand1);
            auto l_val2 = getThePairValueFromOnePair(p_hand2);
            if (l_val1 == l_val2)
            {
                p_hand1.erase(std::remove_if(p_hand1.begin(), p_hand1.end(),
                          [=](auto p){return p.value() == l_val1;}), p_hand1.end());
                p_hand2.erase(std::remove_if(p_hand2.begin(), p_hand2.end(),
                          [=](auto p){return p.value() == l_val1;}), p_hand2.end());
                return findHighestVal(p_hand1) > findHighestVal(p_hand2) ? 1 : -1;
            }
            else
            {
                return l_val1 > l_val2 ? 1 : -1;
            }
        }
        return findHighestVal(p_hand1) > findHighestVal(p_hand2) ? 1 : -1;
    }

    return l_rank1 > l_rank2 ? 1 : -1;
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

int PokerHands::findHighestVal(std::vector<Card> p_hand)
{
    auto l_maxCard = std::max_element(p_hand.begin(),p_hand.end(),
                       [](auto p_card1, auto p_card2){return p_card1.value() < p_card2.value();});

    return l_maxCard->value();
}

int PokerHands::getThePairValueFromOnePair(std::vector<Card> p_hand)
{
    for(auto l_iter = p_hand.begin(); l_iter != p_hand.end(); l_iter++)
    {
       if(2 == std::count_if(p_hand.begin(),p_hand.end(),
                        [&](Card p_card){return p_card.value() == l_iter->value();}))
           return l_iter->value();
    }
    return INVALID_VALUE;
}


