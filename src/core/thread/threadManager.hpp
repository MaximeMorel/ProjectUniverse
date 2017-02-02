#ifndef __THREADMANAGER_HPP__
#define __THREADMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////"
#include "core/engine_export.h"
#include <thread>
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT ThreadManager
{
public:
    ThreadManager();
    ~ThreadManager();

    std::thread& getThread(int i);
    std::thread& getNextThread();

    void joinAll();

private:
    std::thread m_thread[8];
    size_t m_threadUseId;
};
////////////////////////////////////////////////////////////////////////////////
/// Global threads access
void setGlobalThreads(ThreadManager& threads);
ThreadManager ENGINE_EXPORT & threads();
////////////////////////////////////////////////////////////////////////////////
#endif // __THREADMANAGER_HPP__
