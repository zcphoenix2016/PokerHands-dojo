#include <iostream>
#include "../Include/PokerHands.hpp"

#ifndef UNIT_TEST
int main(int argc, char** argv)
#else
int ut_main(int argc, char** argv)
#endif
{
    std::cout << "sum(10, 20) = " << sum(10, 20) << std::endl;

    return 0;
}
