#pragma once

#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>

namespace Heuro
{

    struct ProfileResult
    {
        std::string name;
        std::chrono::milliseconds elapsedTime;
    };

    struct InstrumentationSession
    {
        std::string name;
    };

    class Instrumentor
    {
    private:
        InstrumentationSession *m_CurrentSession;
        std::ofstream m_OutputStream;

    public:
        Instrumentor(const Instrumentor &) = delete;
        Instrumentor(Instrumentor &&) = delete;

        Instrumentor()
            : m_CurrentSession(nullptr)
        {
        }

        ~Instrumentor()
        {
            endSession();
        }

        void beginSession(const std::string &name, const std::string &filepath = "profile.txt")
        {
            if (m_CurrentSession)
            {
                internalEndSession();
            }

            m_OutputStream.open(filepath);

            if (m_OutputStream.is_open())
            {
                m_CurrentSession = new InstrumentationSession{ name };
                writeHeader();
            }
            else
            {
                std::cerr << "Instrumentor could not open output file " << filepath << std::endl;
            }
        }

        void endSession()
        {
            internalEndSession();
        }

        void writeProfile(const ProfileResult &result)
        {
            std::stringstream output;

            output << std::setprecision(3) << std::fixed;
            output << result.name << '\t' << result.elapsedTime.count() << "ms" << '\n';

            if (m_CurrentSession)
            {
                m_OutputStream << output.str();
                m_OutputStream.flush();
            }
        }

        static Instrumentor &get()
        {
            static Instrumentor instance;
            return instance;
        }

    private:
        void writeHeader()
        {
            m_OutputStream << "PROFILING RESULTS" << '\n';
            m_OutputStream.flush();
        }

        void internalEndSession()
        {
            if (m_CurrentSession)
            {
                m_OutputStream.close();
                delete m_CurrentSession;
                m_CurrentSession = nullptr;
            }
        }
    };

    class InstrumentationTimer
    {
    private:
        const char *m_Name;
        std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
        bool m_Stopped;

    public:
        explicit InstrumentationTimer(const char *name)
            : m_Name(name), m_Stopped(false)
        {
            m_StartTimePoint = std::chrono::steady_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
            {
                stop();
            }
        }

        void stop()
        {
            auto endTimePoint = std::chrono::steady_clock::now();

            auto elapsedTime =
                std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch()
                - std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimePoint).time_since_epoch();

            Instrumentor::get().writeProfile({ m_Name, elapsedTime  });

            m_Stopped = true;
        }
    };

}

#ifdef HE_PROFILE
    #define HE_PROFILE_BEGIN_SESSION(name, filepath) ::Heuro::Instrumentor::get().beginSession(name, filepath)
    #define HE_PROFILE_END_SESSION() ::Heuro::Instrumentor::get().endSession()
    #define HE_PROFILE_SCOPE(name) ::Heuro::InstrumentationTimer timer##__LINE__(name)
#else
    #define HE_PROFILE_BEGIN_SESSION(name, filepath)
    #define HE_PROFILE_END_SESSION()
    #define HE_PROFILE_SCOPE(name)
#endif