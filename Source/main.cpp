#include <iostream>
#include "Context.hpp"

#ifndef UNIT_TEST
int main(int argc, char** argv)
#else
int ut_main(int argc, char** argv)
#endif
{
    Context l_context;
    std::cout << "The number of Player-1 wins: " << l_context.handleFile("p054_poker.txt") << std::endl;
    return 0;
}
