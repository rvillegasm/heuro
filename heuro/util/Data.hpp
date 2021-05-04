#pragma once

#include <unordered_set>
#include <ostream>

namespace Heuro
{

    struct ScpResult
    {
        int cost = 0;
        size_t subsetCount = 0;
        std::unordered_set<int> subsetIDs = {};

        std::vector<int> toVec()
        {
            std::vector<int> vec;
            vec.reserve(subsetIDs.size() + 2);
            vec.push_back(cost);
            vec.push_back(static_cast<int>(subsetCount));
            for (int subset : subsetIDs)
            {
                vec.push_back(subset);
            }
            return vec;
        }

        friend std::ostream &operator<<(std::ostream &os, const ScpResult &result)
        {
            os << "cost: " << result.cost << " subsetCount: " << result.subsetCount << " subsetIDs: ";
            for (int id : result.subsetIDs)
            {
                os << id + 1 << " ";
            }
            return os;
        }
    };

    struct ScpInput
    {
        int elementCount = 0; // m
        int subsetCount = 0; // n
        std::vector<int> costs; // Cost of each subset
        std::vector<std::unordered_set<int>> relations; // Relations between each element and the subsets that contain it (e.g index 1: 2, 4 means subsets 2 and 4 contain element 1)
    };

}



