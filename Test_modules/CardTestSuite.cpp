#include "gtest/gtest.h"
#include "Card.hpp"

TEST(CardTestSuite, theValueAndSuitShouldBeTheParameterOfConstructor)
{
    Card l_card{std::string("2H")};

    ASSERT_EQ(2, l_card.value());
    ASSERT_EQ('H', l_card.suit());
}

TEST(CardTestSuite, theCardWithLessValueShouldLoseTheComparer)
{
    Card l_card1{std::string("2H")}, l_card2{std::string("8S")};

    ASSERT_TRUE(l_card1 < l_card2);
    ASSERT_FALSE(l_card2 < l_card1);
}