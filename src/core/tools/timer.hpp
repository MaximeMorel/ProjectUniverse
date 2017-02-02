#ifndef __TIMER_HPP__
#define __TIMER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/log/logger.hpp"
#include "core/engine_export.h"
#include <chrono>
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT Timer
{
public:
    Timer();

    void start();
    void pause();
    void stop();
    void reset();

    std::chrono::microseconds getTime() const;

    static void wait(std::chrono::microseconds microseconds);
    static std::chrono::steady_clock::time_point now();

    friend Logger& operator<<(Logger& o, const Timer& timer);

private:
    std::chrono::steady_clock::time_point m_start;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __TIMER_HPP__
