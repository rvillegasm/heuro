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

        /**
         * @brief Calculates several solutions using a greedy randomized algorithm.
         * If given a noise factor, each cost is modified by +/- the noise factor.
         * The algorithm is based on the one proposed by Mauricio G.C. Resende and Celso C. Ribeiro
         * in "GRASP: Greedy Randomized Adaptive SearchProcedures", under the "A template for Grasp" section.
         *
         * @param maxSolCount The maximum number of iterations the algorithm is allowed.
         * @param k The size of the RCL from which an element will be chosen at random.
         * @param rho The noise factor.
         *
         * @return The cost of the found solution, as well as the chosen subsets count and their IDs.
         */
        ScpResult graspInternal(int maxSolCount, int k, int rho = 0);
        std::unordered_set<int> greedyRandomized(int k, int rho);

    public:
        Scp(int elementCount, int subsetCount, std::vector<int> costs, std::vector<std::unordered_set<int>> relations);

        /**
         * @brief Calculates a solution using a simple greedy algorithm.
         *
         * @return The cost of the found solution, as well as the chosen subsets count and their IDs.
         */
        ScpResult constructive();

        /**
         * @brief Calculates several solutions using a randomized greedy algorithm, and later chooses the best one.
         * During each iteration, it chooses an element at random from the k elements with less cost.
         *
         * @param maxSolCount The maximum number of iterations the algorithm is allowed.
         * @param k The size of the RCL from which an element will be chosen at random.
         *
         * @return The cost of the found solution, as well as the chosen subsets count and their IDs.
         */
        ScpResult grasp(int maxSolCount, int k);

        /**
         * @brief Calculates several solutions using a randomized greedy algorithm and noise, and later chooses the best one.
         * During each iteration, it chooses an element at random from the k elements with less cost.
         * Also, every cost is modified by +/- the noise factor.
         *
         * @param maxSolCount The maximum number of iterations the algorithm is allowed.
         * @param k The size of the RCL from which an element will be chosen at random.
         * @param rho The noise factor.
         *
         * @return The cost of the found solution, as well as the chosen subsets count and their IDs.
         */
        ScpResult graspWithNoise(int maxSolCount, int k, int rho);
    };

}