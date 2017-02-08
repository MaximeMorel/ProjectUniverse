#ifndef __THREADMANAGER_HPP__
#define __THREADMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/engine_export.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT ThreadManager
{
public:
    ThreadManager();
    ~ThreadManager();

    void addTask(const std::function<void()>& taskFunc);

private:
    std::thread m_thread[4];
    size_t m_threadUseId;

    void taskExecutor(int id);

    struct TaskExecutor
    {
        TaskExecutor();
        ~TaskExecutor();

        bool m_stop;
        std::thread m_thread;
        std::mutex m_lock;
        std::condition_variable m_cond;
    } m_taskExecutor[4];

    std::vector<std::function<void()>> m_tasks;
    std::mutex m_tasksLock;
};
////////////////////////////////////////////////////////////////////////////////
/// Global threads access
void setGlobalThreads(ThreadManager& threads);
ThreadManager ENGINE_EXPORT & threads();
////////////////////////////////////////////////////////////////////////////////
#endif // __THREADMANfunction_HPP__
