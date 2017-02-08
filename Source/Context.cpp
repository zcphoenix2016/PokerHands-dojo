#include "Context.hpp"
#include "Card.hpp"
#include <fstream>
#include <vector>

int Context::handleFile(const std::string& p_file)
{
    std::ifstream l_ifs;
    l_ifs.open(p_file);
    if(not l_ifs.is_open())
    {
        return -1;
    }

    int l_count = 0;
    std::string l_card;
    std::vector<Card> l_hand1, l_hand2;
    while(not l_ifs.eof())
    {
        if(5 > l_hand1.size() || 5 > l_hand2.size())
        {
            l_ifs >> l_card;

            if(5 > l_hand1.size())
            {
                l_hand1.emplace_back(l_card);
            }
            else
            {
                l_hand2.emplace_back(l_card);
            }

            continue;
        }

        if(1 == m_pokerHands.compareHands(l_hand1, l_hand2))
        {
            l_count++;
        }

        l_hand1.clear();
        l_hand2.clear();
    }
    l_ifs.close();

    return l_count;
}