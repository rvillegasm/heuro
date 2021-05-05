#pragma once

#include "util/Data.hpp"

#include <vector>
#include <functional>
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

        ScpResult generateNeighbour(const ScpResult& current, int k);
        ScpResult randomNeighbour(const ScpResult &current);
        ScpResult sequentialRemovalNeighbour(const ScpResult &current);
        ScpResult bestNeighbour(const ScpResult &current);

        bool isSolutionFeasible(const std::unordered_set<int> &subsetIDs);
        int calculateSolutionCost(const std::unordered_set<int> &subsetIDs);

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

        /**
         * @brief Tries to find an as-close as possible optimal solution by using a local search meta-heuristic capable of escaping local optima.
         * It allows hill-climbing moves in hopes of finding the global optimum.
         * It simulates the process of physical annealing with solids, in which a crystalline solid is heated and then allowed to cool very slowly
         * until it achieves its most regular possible crystal lattice configuration, and thus is free of crystal defects.
         *
         * (Based on the algorithm proposed in 'Handbook of Metaheuristics', by Michel Gendreau and Jean-Yves Potvin).
         *
         * @param maxRuntime The amount of time in milliseconds for which the algorithm is allowed to run.
         * @param initTemp The initial temperature of the simulation.
         * @param iterPerTemp The number of iterations executed at each temperature.
         * @param tempCoolingSchedule The cooling function. It accepts the initial one and the current iteration number, and returns the new temp..
         *
         * @return The cost of the found solution, as well as the chosen subsets count and their IDs.
         */
        ScpResult simulatedAnnealing(long maxRuntime, double initTemp, int iterPerTemp, const std::function<double(double, int)> &tempCoolingSchedule);

        /**
         * @brief Tries to find an as-close as possible optimal solution by using a variable neighbourhood search method.
         * In it, a neighbour is generated and accepted in case it improves on the current solution.
         * Otherwise, the search continues in another neighbourhood (max. 3 different neighbourhoods).
         *
         * @param maxRuntime The amount of time in milliseconds for which the algorithm is allowed to run.
         *
         * @return The cost of the found solution, as well as the chosen subsets count and their IDs.
         */
        ScpResult vns(long maxRuntime);
    };

}