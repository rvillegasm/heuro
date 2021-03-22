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

}



