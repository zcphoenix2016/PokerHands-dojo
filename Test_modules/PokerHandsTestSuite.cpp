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

    m_hand1 = {std::string("QH"), std::string("6C"), std::string("7S"), std::string("8D"), std::string("TH")};
    ASSERT_EQ(1,   m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1,  m_pokerhands.compare(m_hand2, m_hand1));
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

TEST_F(PokerHandsTestSuite, theHandWithHighCardShouldWinInSameThreeOfAKind)
{
    m_hand1 = {std::string("5H"), std::string("5C"), std::string("5S"), std::string("8D"), std::string("AH")};
    m_hand2 = {std::string("5H"), std::string("5C"), std::string("5S"), std::string("JD"), std::string("AH")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, straightShouldWinThreeOfAKind)
{
    m_hand1 = {std::string("5H"), std::string("5C"), std::string("5S"), std::string("8D"), std::string("AH")};
    m_hand2 = {std::string("5H"), std::string("6C"), std::string("7S"), std::string("8D"), std::string("9H")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighCardShouldWinInTwoStraights)
{
    m_hand1 = {std::string("TH"), std::string("JC"), std::string("QS"), std::string("KD"), std::string("AH")};
    m_hand2 = {std::string("5H"), std::string("6C"), std::string("7S"), std::string("8D"), std::string("9H")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, flushShouldWinStraight)
{
    m_hand1 = {std::string("TH"), std::string("JC"), std::string("QS"), std::string("KD"), std::string("AH")};
    m_hand2 = {std::string("2H"), std::string("6H"), std::string("KH"), std::string("JH"), std::string("9H")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighCardShouldWinInTwoFlushes)
{
    m_hand1 = {std::string("2C"), std::string("JC"), std::string("QC"), std::string("KC"), std::string("AC")};
    m_hand2 = {std::string("2H"), std::string("6H"), std::string("KH"), std::string("JH"), std::string("9H")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, fullHouseShouldWinFlush)
{
    m_hand1 = {std::string("2C"), std::string("2S"), std::string("2D"), std::string("KH"), std::string("KH")};
    m_hand2 = {std::string("2H"), std::string("6H"), std::string("KH"), std::string("JH"), std::string("9H")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHigherThreeOfAKindShouldWinInTwoFullHouses)
{
    m_hand1 = {std::string("2C"), std::string("2S"), std::string("2D"), std::string("KH"), std::string("KH")};
    m_hand2 = {std::string("6H"), std::string("6H"), std::string("6H"), std::string("3D"), std::string("3S")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHigherPairShouldWinInTwoFullHousesWithSameThreeOfAKind)
{
    m_hand1 = {std::string("2C"), std::string("2S"), std::string("2D"), std::string("KH"), std::string("KH")};
    m_hand2 = {std::string("2H"), std::string("2H"), std::string("2H"), std::string("3D"), std::string("3S")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, fourOfAKindShouldWinFullHouse)
{
    m_hand1 = {std::string("2C"), std::string("KS"), std::string("KD"), std::string("KH"), std::string("KH")};
    m_hand2 = {std::string("2H"), std::string("2H"), std::string("2H"), std::string("3D"), std::string("3S")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighestValueShouldWinInSameFourOfAKinds)
{
    m_hand1 = {std::string("8C"), std::string("KS"), std::string("KD"), std::string("KH"), std::string("KH")};
    m_hand2 = {std::string("2H"), std::string("AH"), std::string("AH"), std::string("AD"), std::string("AS")};

    ASSERT_EQ(-1, m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(1,  m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighCardShouldWinInTwoFourOfAKindsWithSameKindValue)
{
    m_hand1 = {std::string("8C"), std::string("KS"), std::string("KD"), std::string("KH"), std::string("KH")};
    m_hand2 = {std::string("2H"), std::string("KH"), std::string("KH"), std::string("KD"), std::string("KS")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, straightFlushShouldWinFourOfAKind)
{
    m_hand1 = {std::string("8S"), std::string("9S"), std::string("TS"), std::string("JS"), std::string("QS")};
    m_hand2 = {std::string("2H"), std::string("KH"), std::string("KH"), std::string("KD"), std::string("KS")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, theHandWithHighCardShouldWinInTwoStraightFlush)
{
    m_hand1 = {std::string("8S"), std::string("9S"), std::string("TS"), std::string("JS"), std::string("QS")};
    m_hand2 = {std::string("2H"), std::string("3H"), std::string("4H"), std::string("5H"), std::string("6H")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}

TEST_F(PokerHandsTestSuite, royalFlushShouldWinstraightFlush)
{
    m_hand1 = {std::string("TS"), std::string("JS"), std::string("QS"), std::string("KS"), std::string("AS")};
    m_hand2 = {std::string("8S"), std::string("9S"), std::string("TS"), std::string("JS"), std::string("QS")};

    ASSERT_EQ(1,  m_pokerhands.compare(m_hand1, m_hand2));
    ASSERT_EQ(-1, m_pokerhands.compare(m_hand2, m_hand1));
}
