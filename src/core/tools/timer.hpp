#ifndef __TIMER_HPP__
#define __TIMER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/log/logger.hpp"
////////////////////////////////////////////////////////////////////////////////
class Timer
{
public:
    Timer();

    void start();
    void pause();
    void stop();
    void reset();

    double getTime() const;

    static void wait(double milliseconds);
    static double now();

    friend Logger& operator<<(Logger& o, const Timer& timer);

private:
    double m_start;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __TIMER_HPP__
