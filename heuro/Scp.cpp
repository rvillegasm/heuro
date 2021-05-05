#include "Scp.hpp"

#include "util/RandomIntGenerator.hpp"
#include "util/RandomRealGenerator.hpp"
#include "util/Timer.hpp"

#include <algorithm>
#include <numeric>
#include <utility>

namespace Heuro
{
    namespace Util
    {
        static std::vector<int> findMinIndices(const std::vector<int> &vec, int n)
        {
            std::vector<int> indices(vec.size());
            std::iota(indices.begin(), indices.end(), 0);

            std::partial_sort(indices.begin(), indices.begin() + n, indices.end(), [&vec](int i, int j) { return vec[i] < vec[j]; });
            return std::vector<int>(indices.begin(), indices.begin() + n);
        }

        static auto findMinSubsetCost(const std::vector<std::pair<std::unordered_set<int>, int>> &subsets)
        {
            return std::min_element(
                subsets.begin(),
                subsets.end(),
                [](const auto &a, const auto &b)
                {
                    return a.second < b.second;
                }
            );
        }
    }

    Scp::Scp(int elementCount, int subsetCount, std::vector<int> costs, std::vector<std::unordered_set<int>> relations)
        : m_ElementCount(elementCount), m_SubsetCount(subsetCount), m_Costs(std::move(costs)), m_Relations(std::move(relations))
    {
    }

    ScpResult Scp::constructive()
    {
        return graspInternal(1, 1);
    }

    ScpResult Scp::grasp(int maxSolCount, int k)
    {
        return graspInternal(maxSolCount, k);
    }

    ScpResult Scp::graspWithNoise(int maxSolCount, int k, int rho)
    {
        return graspInternal(maxSolCount, k, rho);
    }

    ScpResult Scp::simulatedAnnealing(long maxRuntime, double initTemp, int iterPerTemp, const std::function<double(double, int)> &tempCoolingSchedule)
    {
        ScpResult currentSolution = constructive();
        RandomRealGenerator randGen(0.0, 1.0);

        int iterCount = 0;
        double currentTemp = initTemp;
        Timer timer(maxRuntime);
        while (!timer.hasStopped() && currentTemp > 0.0)
        {
            for (int i = 0; i < iterPerTemp; ++i)
            {
                ScpResult neighbourSolution = generateNeighbour(currentSolution, 0);

                int deltaCost = neighbourSolution.cost - currentSolution.cost;
                if (deltaCost <= 0)
                {
                    currentSolution = std::move(neighbourSolution);
                }
                else
                {
                    double acceptanceProbability = exp(-deltaCost / currentTemp);
                    if (randGen() <= acceptanceProbability)
                    {
                        currentSolution = std::move(neighbourSolution);
                    }
                }
            }

            iterCount += 1;
            timer.tick();
            currentTemp = tempCoolingSchedule(initTemp, iterCount);
        }

        return currentSolution;
    }

    ScpResult Scp::vns(long maxRuntime)
    {
        ScpResult currentSolution = constructive();

        Timer timer(maxRuntime);
        while (!timer.hasStopped())
        {
            for (int k = 0; k < 3; ++k)
            {
                ScpResult neighbourSolution = generateNeighbour(currentSolution, k);
                int deltaCost = neighbourSolution.cost - currentSolution.cost;
                if (deltaCost <= 0)
                {
                    currentSolution = std::move(neighbourSolution);
                    break;
                }
            }

            timer.tick();
        }

        return currentSolution;
    }

    ScpResult Scp::graspInternal(int maxSolCount, int k, int rho)
    {
        std::vector<std::pair<std::unordered_set<int>, int>> foundSolutions; // list of solutions and costs
        foundSolutions.reserve(maxSolCount);

        for (int i = 0; i < maxSolCount; ++i)
        {
            auto solution = greedyRandomized(k, rho);
            int solutionCost = calculateSolutionCost(solution);

            foundSolutions.emplace_back(std::move(solution), solutionCost);
        }

        std::pair<std::unordered_set<int>, int> bestSolution = *Util::findMinSubsetCost(foundSolutions);

        return ScpResult{ bestSolution.second, bestSolution.first.size(), std::move(bestSolution.first) };
    }

    std::unordered_set<int> Scp::greedyRandomized(int k, int rho)
    {
        std::unordered_set<int> solution; // subset IDs
        std::vector<int> localCosts(m_Costs); // local copy to avoid mangling the OG
        std::vector<std::unordered_set<int>> localRelations(m_Relations);
        std::unordered_set<int> remainingElements;
        remainingElements.reserve(m_ElementCount);
        for (int i = 0; i < m_ElementCount; ++i)
        {
            remainingElements.insert(i);
        }

        if (rho)
        {
            for (int &cost : localCosts)
            {
                cost = RandomIntGenerator(cost - rho, cost + rho)();
            }
        }

        RandomIntGenerator randGen(0, k);
        while (!remainingElements.empty())
        {
            std::vector<int> subsetRestrictedCandidatesList = Util::findMinIndices(localCosts, k); // NOTE: k has to be less than n
            int randomNumber = randGen();
            int chosenSubsetCandidate = subsetRestrictedCandidatesList[randomNumber];
            for (int i = 0; i < localRelations.size(); ++i)
            {
                if (localRelations[i].contains(chosenSubsetCandidate))
                {
                    solution.insert(chosenSubsetCandidate);
                    remainingElements.erase(i);
                    localRelations[i].clear(); // mark the relation as used since the item has been selected
                }
            }
            localCosts[chosenSubsetCandidate] = std::numeric_limits<int>::max(); // marks the value as already used
        }

        return solution;
    }

    ScpResult Scp::generateNeighbour(const ScpResult &current, int k)
    {
        switch (k)
        {
            case 0:
                return randomNeighbour(current);
            case 1:
                return sequentialRemovalNeighbour(current);
            case 2:
                return bestNeighbour(current);
            default:
                return ScpResult();
        }
    }

    ScpResult Scp::randomNeighbour(const ScpResult &current)
    {
        RandomIntGenerator randSubsetGen(0, m_SubsetCount);

        std::unordered_set<int> subsetIDs = current.subsetIDs;
        std::vector<int> subsetIDsList(subsetIDs.begin(), subsetIDs.end());
        RandomIntGenerator randIndexGen(0, static_cast<int>(subsetIDsList.size()));
        do
        {
            int subsetToRemove = subsetIDsList[randIndexGen()];
            int subsetToAdd = randSubsetGen();
            subsetIDs.erase(subsetToRemove);
            subsetIDs.insert(subsetToAdd); // since the generated number could already be inside the set, add 0 or 1 new subset
        }
        while (!isSolutionFeasible(subsetIDs));

        return { calculateSolutionCost(subsetIDs), subsetIDs.size(), std::move(subsetIDs) };
    }

    ScpResult Scp::sequentialRemovalNeighbour(const ScpResult &current)
    {
        RandomIntGenerator randSubsetGen(0, m_SubsetCount);

        ScpResult selectedNeighbour = current;
        std::unordered_set<int> subsetIDs = selectedNeighbour.subsetIDs;
        std::vector<int> subsetIDsList(selectedNeighbour.subsetIDs.begin(), selectedNeighbour.subsetIDs.end()); // Just for iteration, because of access violation when iterating the set

        int minCost = std::numeric_limits<int>::max();
        for (int subset : subsetIDsList)
        {
            int subsetToAdd = randSubsetGen();
            subsetIDs.erase(subset);
            subsetIDs.insert(subsetToAdd);
            int cost = calculateSolutionCost(subsetIDs);
            if (cost <= minCost && isSolutionFeasible(subsetIDs))
            {
                minCost = cost;
                selectedNeighbour = { cost, subsetIDs.size(), subsetIDs };
            }
            // roll back to explore other options
            subsetIDs.erase(subsetToAdd);
            subsetIDs.insert(subset);
        }

        return selectedNeighbour;
    }

    ScpResult Scp::bestNeighbour(const ScpResult &current)
    {
        // sequentially eliminate one and add another (O(n^2)). choose the best one.
        ScpResult bestNeighbour = current;
        std::unordered_set<int> subsetIDs = bestNeighbour.subsetIDs;
        std::vector<int> subsetIDsList(bestNeighbour.subsetIDs.begin(), bestNeighbour.subsetIDs.end()); // Just for iteration, because of access violation when iterating the set

        int minCost = std::numeric_limits<int>::max();
        for (int subset : subsetIDsList)
        {
            subsetIDs.erase(subset);
            for (int i = 0; i < m_SubsetCount; ++i)
            {
                subsetIDs.insert(i);
                int cost = calculateSolutionCost(subsetIDs);
                if (cost <= minCost && isSolutionFeasible(subsetIDs))
                {
                    minCost = cost;
                    bestNeighbour = { cost, subsetIDs.size(), subsetIDs };
                }

                subsetIDs.erase(i);
            }
            subsetIDs.insert(subset);
        }

        return bestNeighbour;
    }

    bool Scp::isSolutionFeasible(const std::unordered_set<int> &subsetIDs)
    {
        std::unordered_set<int> remainingElements;
        remainingElements.reserve(m_ElementCount);
        for (int i = 0; i < m_ElementCount; ++i)
        {
            remainingElements.insert(i);
        }

        for (int i = 0; i < m_Relations.size(); ++i)
        {
            for (int subset : subsetIDs)
            {
                if (m_Relations[i].contains(subset))
                {
                    remainingElements.erase(i); // if the element is contained by the subset, mark it as used
                    break;
                }
            }
        }

        return remainingElements.empty(); // all elements must be taken into account for the solution to be feasible
    }

    int Scp::calculateSolutionCost(const std::unordered_set<int> &subsetIDs)
    {
        return std::reduce(subsetIDs.begin(), subsetIDs.end(), 0, [this](int a, int b) { return a + m_Costs[b]; });
    }
}