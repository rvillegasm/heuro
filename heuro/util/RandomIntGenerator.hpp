#pragma once

#include <random>

namespace Heuro
{

    class RandomIntGenerator
    {
    private:
        std::mt19937 m_RandomEngine;
        std::uniform_int_distribution<int> m_Distribution;

    public:
        RandomIntGenerator(int low, int high)
            : m_RandomEngine(std::random_device{}()), m_Distribution(low, high - 1)
        {
        }

        int operator()()
        {
            return m_Distribution(m_RandomEngine);
        }
    };

}



