// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: DeltaTime.h
// Date: 01/11/2019

#pragma once

namespace midori {

    class DeltaTime {
    public:
        DeltaTime(float time = 0.0f)
            : m_Time(time) {}

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }

        float GetMilliseconds() const { return m_Time * 1000.0f; }

    private:
        float m_Time;
    };

}
