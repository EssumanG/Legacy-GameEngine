#pragma once

namespace Legacy
{

    class Timestep
    {
    public:
        Timestep(float time = 0.0)
            :m_Time(time)
        {
        }
        float GetTime() { return m_Time; }
        float GetTimeSeconds() { return m_Time; }
        float GetMilliSeconds() { return m_Time * 1000.0; }

    private:
        float m_Time;

    };
}

