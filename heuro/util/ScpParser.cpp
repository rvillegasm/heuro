#include "ScpParser.hpp"

#include <fstream>
#include <utility>

namespace Heuro
{

    ScpInput ScpParser::parseFile(const std::string &filename)
    {
        std::ifstream inputFile(filename);
        int m, n;
        std::vector<int> costs;
        std::vector<std::unordered_set<int>> relations;

        bool test = inputFile.is_open();
        inputFile >> m;
        inputFile >> n;

        costs.reserve(n);
        for (int i = 0; i < n; ++i)
        {
            int cost;
            inputFile >> cost;
            costs.push_back(cost);
        }

        relations.reserve(m);
        for (int i = 0; i < m; ++i)
        {
            int numOfSubsets;
            inputFile >> numOfSubsets;
            std::unordered_set<int> relation(numOfSubsets);
            for (int j = 0; j < numOfSubsets; ++j)
            {
                int subset;
                inputFile >> subset;
                relation.insert(subset - 1);
            }
            relations.push_back(std::move(relation));
        }

        return ScpInput{ m, n, std::move(costs), std::move(relations) };
    }

}