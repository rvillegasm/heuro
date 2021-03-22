#pragma once

#include "util/Data.hpp"

#include <vector>
#include <unordered_set>

namespace Heuro
{

    class Scp
    {
    private:
        int m_ElementCount = 0; // m
        int m_SubsetCount = 0; // n
        std::vector<int> m_Costs; // Cost of each subset
        std::vector<std::unordered_set<int>> m_Relations; // Relations between each element and the subsets that contain it (e.g index 1: 2, 4 means subsets 2 and 4 contain element 1)

        std::unordered_set<int> greedyRandomized(int k);

    public:
        Scp(int elementCount, int subsetCount, std::vector<int> costs, std::vector<std::unordered_set<int>> relations);

        ScpResult constructive();
        ScpResult grasp(int maxSolCount, int k);
    };

}