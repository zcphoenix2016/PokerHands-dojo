#include "gtest/gtest.h"
#include "PokerHands.hpp"

class PokerHandsTestSuite : public ::testing::Test
{
public:
    vector<Card> m_hand1;
    vector<Card> m_hand2;
    PokerHands   m_pokerhands;
};

TEST_F(PokerHandsTestSuite, onePairShouldWinHighCard)
{
    m_hand1 = {string("5H"), string("6C"), string("7S"), string("8D"), string("TH")};
    m_hand2 = {string("5H"), string("5C"), string("7S"), string("8D"), string("TH")};
    
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, twoPairsShouldWinOnePair)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("7D"), string("TH")};
    m_hand2 = {string("5H"), string("5C"), string("7S"), string("8D"), string("TH")};
    
    ASSERT_EQ(1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, oneHighCardWithHighestValueShouldWinTheOtherHighCard)
{
    m_hand1 = {string("5H"), string("4C"), string("7S"), string("8D"), string("TH")};
    m_hand2 = {string("QH"), string("5C"), string("7S"), string("8D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, onePairCardWithHighestValueShouldWinOnePairWithLessValue)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("8D"), string("TH")};
    m_hand2 = {string("QH"), string("7C"), string("7S"), string("8D"), string("TH")};
    
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighestValueShouldWinInTwoHandsWithOneSamePair)
{
    m_hand1 = {string("5H"), string("5C"), string("7S"), string("8D"), string("TH")};
    m_hand2 = {string("QH"), string("5C"), string("5S"), string("8D"), string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1, m_pokerhands.compare(m_hand2, m_hand1));
}
