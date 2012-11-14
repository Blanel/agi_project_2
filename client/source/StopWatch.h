#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include <chrono>
#include "Types.h"

#include <functional>
#include <memory>

namespace revel
{

class StopWatch
{
protected:
    std::chrono::high_resolution_clock::time_point m_InitialTimePoint;

public:
    StopWatch()
        : m_InitialTimePoint(std::chrono::high_resolution_clock::now())
    {}

    f64 elapsed_time() const
    {
        std::chrono::duration<f64, std::ratio<1>> dur = std::chrono::high_resolution_clock::now() - m_InitialTimePoint;

        return dur.count();
    }

    void reset()
    {
        m_InitialTimePoint = std::chrono::high_resolution_clock::now();
    }
};

/*
template <typename T>
class Timer
{
    std::function<void(T&)> m_Callback;

    std::chrono::high_resolution_clock::time_point m_InitTime;
    std::chrono::high_resolution_clock::time_point m_TargetTime;

    bool m_Continous;

public:
    Timer()
    {

    }

};
*/

} // ::revel

#endif // STOPWATCH_H_
