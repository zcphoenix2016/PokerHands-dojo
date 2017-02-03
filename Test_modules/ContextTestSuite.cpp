#include "gtest/gtest.h"
#include "Card.hpp"
#include "Context.hpp"
#include <string>

TEST(ContextTestSuite, testHandleFile)
{
    Context l_context;
    std::string l_file{"p054_poker.txt"};
    ASSERT_EQ(376, l_context.handleFile(l_file));
}

