#pragma once

#include <random>

namespace Heuro
{

    class RandomBinaryGenerator
    {
    private:
        std::mt19937 m_RandomEngine;
        std::bernoulli_distribution m_Distribution;

    public:
        explicit RandomBinaryGenerator(double probability = 0.5)
            : m_RandomEngine(std::random_device{}()), m_Distribution(probability)
        {
        }

        int operator()()
        {
            return m_Distribution(m_RandomEngine);
        }
    };

}


