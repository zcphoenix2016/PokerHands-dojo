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

    return std::lexicographical_compare(p_hand1.begin(), p_hand1.end(),
                                        p_hand2.begin(), p_hand2.end(),
                                        l_comparer) ? -1 : 1;
}

int PokerHands::compareOnePair(std::vector<Card> p_hand1, std::vector<Card> p_hand2)
{
    int l_valueOfPair1 = valuesOfPairs(p_hand1).front();
    int l_valueOfPair2 = valuesOfPairs(p_hand2).front();
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
    std::vector<int> l_valuesOfPair1 = valuesOfPairs(p_hand1);
    std::vector<int> l_valuesOfPair2 = valuesOfPairs(p_hand2);

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
    int l_valueOfThreeKind1 = findValueOfThreeKind(p_hand1);
    int l_valueOfThreeKind2 = findValueOfThreeKind(p_hand2);

    if(l_valueOfThreeKind1 != l_valueOfThreeKind2)
    {
        return l_valueOfThreeKind1 > l_valueOfThreeKind2 ? 1 : -1;
    }
    else
    {
        std::vector<Card> l_handWithoutThreeKind1{}, l_handWithoutThreeKind2{};
        std::copy_if(p_hand1.begin(), p_hand1.end(), std::back_inserter(l_handWithoutThreeKind1),
                     [=](auto p_card){return p_card.value() != l_valueOfThreeKind1;});
        std::copy_if(p_hand2.begin(), p_hand2.end(), std::back_inserter(l_handWithoutThreeKind2),
                     [=](auto p_card){return p_card.value() != l_valueOfThreeKind2;});

        return compareHighCard(l_handWithoutThreeKind1, l_handWithoutThreeKind2);
    }
}

int PokerHands::findValueOfThreeKind(std::vector<Card> p_hand)
{
    auto l_card = p_hand.begin();
    while(l_card != p_hand.end())
    {
        if(3 == std::count_if(p_hand.begin(), p_hand.end(),
                              [&](auto p_card){return p_card.value() == l_card->value();}))
        {
            return l_card->value();
        }
        l_card ++;
    }
    
    return INVALID_VALUE;
}

bool PokerHands::isThreeKind(std::vector<Card> p_hand)
{
    auto l_card = p_hand.begin();
    while(l_card != p_hand.end())
    {
        if(3 == std::count_if(p_hand.begin(), p_hand.end(),
                              [&](auto p_card){return p_card.value() == l_card->value();}))
        {
            return true;
        }
        l_card ++;
    }

    return false;
}

HandRank PokerHands::calcRank(std::vector<Card> p_hand)
{
    HandRank l_rank = HAND_RANK_HIGH_CARD;

    if(isThreeKind(p_hand))
    {
        l_rank = HAND_RANK_THREE_KIND;
    }
    else
    {
        std::vector<int> l_valuesOfPairs = valuesOfPairs(p_hand);

        if(2 == l_valuesOfPairs.size())
        {
            l_rank = HAND_RANK_TWO_PAIRS;
        }
        else if(1 == l_valuesOfPairs.size())
        {
            l_rank = HAND_RANK_ONE_PAIR;
        }
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


