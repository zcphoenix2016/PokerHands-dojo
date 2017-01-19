#include "gtest/gtest.h"
#include "PokerHands.hpp"

TEST(PokerHandsTestSuite, onePairShouldWinHighCard)
{
    vector<Card> cards1, cards2;
    cards1.emplace_back("5H");
    cards1.emplace_back("6C");
    cards1.emplace_back("7S");
    cards1.emplace_back("8D");
    cards1.emplace_back("TH");
    
    cards2.emplace_back("5H");
    cards2.emplace_back("5C");
    cards2.emplace_back("7S");
    cards2.emplace_back("8D");
    cards2.emplace_back("TH");
    
    ASSERT_EQ(-1, PokerHands::compare(cards1, cards2));
    ASSERT_EQ(1, PokerHands::compare(cards2, cards1));
}

TEST(PokerHandsTestSuite, twoPairsShouldWinOnePair)
{
    vector<Card> cards1, cards2;
    cards1.emplace_back("5H");
    cards1.emplace_back("5C");
    cards1.emplace_back("7S");
    cards1.emplace_back("7D");
    cards1.emplace_back("TH");
    
    cards2.emplace_back("5H");
    cards2.emplace_back("5C");
    cards2.emplace_back("7S");
    cards2.emplace_back("8D");
    cards2.emplace_back("TH");
    
    ASSERT_EQ(1, PokerHands::compare(cards1, cards2));
}

TEST(PokerHandsTestSuite, oneHighCardWithHighestValueShouldWinTheOtherHighCard)
{
    vector<Card> cards1, cards2;
    cards1.emplace_back("5H");
    cards1.emplace_back("4C");
    cards1.emplace_back("7S");
    cards1.emplace_back("8D");
    cards1.emplace_back("TH");
    
    cards2.emplace_back("QH");
    cards2.emplace_back("5C");
    cards2.emplace_back("7S");
    cards2.emplace_back("8D");
    cards2.emplace_back("TH");
    
    ASSERT_EQ(-1, PokerHands::compare(cards1, cards2));
    ASSERT_EQ(1, PokerHands::compare(cards2, cards1));
}