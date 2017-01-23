#include "PokerHands.hpp"
#include <algorithm>

int PokerHands::compare(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    CardsRank l_c1 = calcRank(p_hand1);
    CardsRank l_c2 = calcRank(p_hand2);

    if(l_c1 == l_c2)
    {
        if(l_c1 == CARDS_RANK_ONE_PAIR)
        {
            auto l_val1 = getThePairValueFromOnePair(p_hand1);
            auto l_val2 = getThePairValueFromOnePair(p_hand2);
            if (l_val1 == l_val2)
            {
                p_hand1.erase(remove_if(p_hand1.begin(), p_hand1.end(),
                          [=](auto p){return p.value() == l_val1;}), p_hand1.end());
                p_hand2.erase(remove_if(p_hand2.begin(), p_hand2.end(),
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

    return l_c1 > l_c2 ? 1 : -1;
}

CardsRank PokerHands::calcRank(std::vector<Card> p_hand)
{
    CardsRank l_cr = CARDS_RANK_HIGH_CARD;

    if (isTwoPairs(p_hand))
    {
        l_cr = CARDS_RANK_TWO_PAIRS;
    }
    else if (isOnePair(p_hand))
    {
        l_cr = CARDS_RANK_ONE_PAIR;
    }

    return l_cr;
}

bool PokerHands::isOnePair(std::vector<Card> p_hand)
{
    for(auto l_iter = p_hand.begin(); l_iter != p_hand.end(); l_iter++)
    {
       if(2 == count_if(p_hand.begin(),p_hand.end(),
                        [&](Card p_card){return p_card.value() == l_iter->value();}))
           return true;
    }
    return false;
}


bool PokerHands::isTwoPairs(std::vector<Card> p_hand)
{
    sort(p_hand.begin(), p_hand.end(),
         [](auto p_card1, auto p_card2){return p_card1.value() < p_card2.value();});

    int count = 0;
    for(auto l_iter = p_hand.begin(); l_iter != p_hand.end(); l_iter++)
    {
        if(2 == count_if(p_hand.begin(),p_hand.end(),
                        [&](Card p_card){return p_card.value() == l_iter->value();}))
        {
            count++;
            l_iter++;
        }
    }

    if (2 == count)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int PokerHands::findHighestVal(std::vector<Card> p_hand)
{
    auto l_maxCard = max_element(p_hand.begin(),p_hand.end(),
                       [](auto p_card1, auto p_card2){return p_card1.value() < p_card2.value();});

    return l_maxCard->value();
}

int PokerHands::getThePairValueFromOnePair(std::vector<Card> p_hand)
{
    for(auto l_iter = p_hand.begin(); l_iter != p_hand.end(); l_iter++)
    {
       if(2 == count_if(p_hand.begin(),p_hand.end(),
                        [&](Card p_card){return p_card.value() == l_iter->value();}))
           return l_iter->value();
    }
    return INVALID_VALUE;
}


