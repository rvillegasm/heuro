#pragma once

#include <chrono>

namespace Heuro
{

    class Timer
    {
    private:
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
        long m_MaxDurationMillis;
        bool m_Stopped;

        void checkIfDone(long elapsedMillis);

    public:
        explicit Timer(long maxDurationMillis);

        void tick();
        bool hasStopped() const;
    };

}


