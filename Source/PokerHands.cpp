#include "PokerHands.hpp"
#include <algorithm>

int PokerHands::compare(std::vector<Card> p_cards1, std::vector<Card> p_cards2)
{
    CardsRank l_c1 = calcRank(p_cards1);
    CardsRank l_c2 = calcRank(p_cards2);

    if(l_c1 == l_c2)
    {
        if(l_c1 == CARDS_RANK_ONE_PAIR)
        {
            auto l_val1 = getThePairValueFromOnePair(p_cards1);
            auto l_val2 = getThePairValueFromOnePair(p_cards2);
            if (l_val1 == l_val2)
            {
                p_cards1.erase(remove_if(p_cards1.begin(), p_cards1.end(),
                          [=](auto p){return p.value() == l_val1;}), p_cards1.end());
                p_cards2.erase(remove_if(p_cards2.begin(), p_cards2.end(),
                          [=](auto p){return p.value() == l_val1;}), p_cards2.end());
                return findHighestVal(p_cards1) > findHighestVal(p_cards2) ? 1 : -1;
            }
            else
            {
                return l_val1 > l_val2 ? 1 : -1;
            }
        }
        return findHighestVal(p_cards1) > findHighestVal(p_cards2) ? 1 : -1;
    }

    return l_c1 > l_c2 ? 1 : -1;
}

CardsRank PokerHands::calcRank(std::vector<Card> p_cards)
{
    CardsRank l_cr = CARDS_RANK_HIGH_CARD;

    if (isTwoPairs(p_cards))
    {
        l_cr = CARDS_RANK_TWO_PAIRS;
    }
    else if (isOnePair(p_cards))
    {
        l_cr = CARDS_RANK_ONE_PAIR;
    }

    return l_cr;
}

bool PokerHands::isOnePair(std::vector<Card> p_cards)
{
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(2 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.value() == l_iter->value();}))
           return true;
    }
    return false;
}


bool PokerHands::isTwoPairs(std::vector<Card> p_cards)
{
    sort(p_cards.begin(), p_cards.end(),
         [](auto p_card1, auto p_card2){return p_card1.value() < p_card2.value();});

    int count = 0;
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
        if(2 == count_if(p_cards.begin(),p_cards.end(),
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

int PokerHands::findHighestVal(std::vector<Card> p_cards)
{
    auto l_maxCard = max_element(p_cards.begin(),p_cards.end(),
                       [](auto p_card1, auto p_card2){return p_card1.value() < p_card2.value();});

    return l_maxCard->value();
}

int PokerHands::getThePairValueFromOnePair(std::vector<Card> p_cards)
{
    for(auto l_iter = p_cards.begin(); l_iter != p_cards.end(); l_iter++)
    {
       if(2 == count_if(p_cards.begin(),p_cards.end(),
                        [&](Card p){return p.value() == l_iter->value();}))
           return l_iter->value();
    }
    return INVALID_VALUE;
}


