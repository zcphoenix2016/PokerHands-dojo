#include "gtest/gtest.h"
#include "Card.hpp"
#include "PokerHands.hpp"

class PokerHandsTestSuite : public ::testing::Test
{
public:
    std::vector<Card> m_hand1;
    std::vector<Card> m_hand2;
    PokerHands        m_pokerhands;
};

TEST_F(PokerHandsTestSuite, onePairShouldWinHighCard)
{
    m_hand1 = {std::string("5H"), std::string("6C"), std::string("7S"), std::string("8D"), std::string("TH")};
    m_hand2 = {std::string("5H"), std::string("5C"), std::string("7S"), std::string("8D"), std::string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, twoPairsShouldWinOnePair)
{
    m_hand1 = {std::string("5H"), std::string("5C"), std::string("7S"), std::string("7D"), std::string("TH")};
    m_hand2 = {std::string("5H"), std::string("5C"), std::string("7S"), std::string("8D"), std::string("TH")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, oneHighCardWithHighestValueShouldWinTheOtherHighCard)
{
    m_hand1 = {std::string("5H"), std::string("4C"), std::string("7S"), std::string("8D"), std::string("TH")};
    m_hand2 = {std::string("QH"), std::string("5C"), std::string("7S"), std::string("8D"), std::string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, onePairWithHighestValueShouldWinOnePairWithLessValue)
{
    m_hand1 = {std::string("5H"), std::string("5C"), std::string("7S"), std::string("8D"), std::string("TH")};
    m_hand2 = {std::string("QH"), std::string("7C"), std::string("7S"), std::string("8D"), std::string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighestValueShouldWinInSameOnePair)
{
    m_hand1 = {std::string("5H"), std::string("5C"), std::string("7S"), std::string("8D"), std::string("TH")};
    m_hand2 = {std::string("QH"), std::string("5C"), std::string("5S"), std::string("8D"), std::string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, twoPairWithHighestValueShouldWinTwoPairWithLessValue)
{
    m_hand1 = {std::string("5H"), std::string("5C"), std::string("QS"), std::string("QD"), std::string("TH")};
    m_hand2 = {std::string("QH"), std::string("7C"), std::string("7S"), std::string("QD"), std::string("TH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighestValueShouldWinInSameTwoPairs)
{
    m_hand1 = {std::string("5H"), std::string("5C"), std::string("8S"), std::string("8D"), std::string("TH")};
    m_hand2 = {std::string("5H"), std::string("5C"), std::string("8S"), std::string("8D"), std::string("AH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, ThreeOfAKindShouldWinTwoPairs)
{
    m_hand1 = {std::string("5H"), std::string("5C"), std::string("8S"), std::string("8D"), std::string("TH")};
    m_hand2 = {std::string("5H"), std::string("5C"), std::string("5S"), std::string("8D"), std::string("AH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighestValueShouldWinInSameThreeOfAKind)
{
    m_hand1 = {std::string("5H"), std::string("8C"), std::string("8S"), std::string("8D"), std::string("TH")};
    m_hand2 = {std::string("5H"), std::string("5C"), std::string("5S"), std::string("8D"), std::string("AH")};

    ASSERT_EQ(1,   m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1,  m_pokerhands.compare(m_hand2, m_hand1));
}
