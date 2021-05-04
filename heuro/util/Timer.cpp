#include "Timer.hpp"

namespace Heuro
{

    Timer::Timer(long maxDurationMillis)
        : m_MaxDurationMillis(maxDurationMillis), m_Stopped(false)
    {
        m_StartTimePoint = std::chrono::steady_clock::now();
    }

    void Timer::tick()
    {
        auto currentTimePoint = std::chrono::steady_clock::now();
        auto elapsedTime =
            std::chrono::time_point_cast<std::chrono::milliseconds>(currentTimePoint).time_since_epoch()
            - std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimePoint).time_since_epoch();

        checkIfDone(elapsedTime.count());
    }

    bool Timer::hasStopped() const
    {
        return m_Stopped;
    }

    void Timer::checkIfDone(long elapsedMillis)
    {
        if (elapsedMillis >= m_MaxDurationMillis)
        {
            m_Stopped = true;
        }
    }

}