#pragma once

#include <random>

namespace Heuro
{

    class RandomRealGenerator
    {
    private:
        std::mt19937 m_RandomEngine;
        std::uniform_real_distribution<double> m_Distribution;

    public:
        RandomRealGenerator(double low, double high)
            : m_RandomEngine(std::random_device{}()), m_Distribution(low, high)
        {
        }

        double operator()()
        {
            return m_Distribution(m_RandomEngine);
        }
    };

}


