////////////////////////////////////////////////////////////////////////////////
#include "threadManager.hpp"
////////////////////////////////////////////////////////////////////////////////
ThreadManager* gThreads = nullptr;
////////////////////////////////////////////////////////////////////////////////
ThreadManager::ThreadManager()
    : m_threadUseId(0)
{
    for (int i = 0; i < 4; ++i)
    {
        m_taskExecutor[i].m_thread = std::thread(&ThreadManager::taskExecutor, this, i);
    }
}
////////////////////////////////////////////////////////////////////////////////
ThreadManager::~ThreadManager()
{
}
////////////////////////////////////////////////////////////////////////////////
void ThreadManager::addTask(const std::function<void()>& taskFunc)
{
    {
        std::lock_guard<std::mutex> lock(m_tasksLock);
        m_tasks.push_back(taskFunc);
    }
    m_taskExecutor[0].m_cond.notify_one();
}
////////////////////////////////////////////////////////////////////////////////
void ThreadManager::taskExecutor(int id)
{
    // pick a task and pop it from the list
    // if we have some other tasks pending, wake the next thread to handle it
    // execute the task
    // wait for notification

    TaskExecutor& t = m_taskExecutor[id];
    TaskExecutor& tNext = m_taskExecutor[(id + 1) % 4];

    while (!t.m_stop)
    {
        std::unique_lock<std::mutex> execLock(t.m_lock);
        t.m_cond.wait(execLock);
        std::unique_lock<std::mutex> lock(m_tasksLock);
        if (m_tasks.empty())
            continue;
        std::function<void()> taskFunc = m_tasks.back();
        m_tasks.pop_back();
        if (!m_tasks.empty())
        {
            // notify another thread as we still have tasks pending
            tNext.m_cond.notify_one();
        }
        lock.unlock();
        taskFunc();
    }
}
////////////////////////////////////////////////////////////////////////////////
ThreadManager::TaskExecutor::TaskExecutor()
    : m_stop(false)
{}
////////////////////////////////////////////////////////////////////////////////
ThreadManager::TaskExecutor::~TaskExecutor()
{
    m_stop = true;
    m_cond.notify_one();
    if (m_thread.joinable())
        m_thread.join();
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
void setGlobalThreads(ThreadManager& threads)
{
    gThreads = &threads;
}
////////////////////////////////////////////////////////////////////////////////
ThreadManager& threads()
{
    return *gThreads;
}
////////////////////////////////////////////////////////////////////////////////
