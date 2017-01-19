////////////////////////////////////////////////////////////////////////////////
#include "logManager.hpp"
#include <iostream>
////////////////////////////////////////////////////////////////////////////////
LogManager* gLog = nullptr;
////////////////////////////////////////////////////////////////////////////////
LogManager::LogManager()
{
    LoggerGroup* logAll = new LoggerGroup("all");
    LoggerStream* logStdout =  new LoggerStream("stdout", std::cout);
    LoggerFile* logFile = new LoggerFile("log", "engine.log");

    logAll->addLogger(logStdout);
    logAll->addLogger(logFile);

    m_loggers.push_back(logAll);
    m_loggers.push_back(logStdout);
    m_loggers.push_back(logFile);
}
////////////////////////////////////////////////////////////////////////////////
LogManager::~LogManager()
{
    for (auto* logger : m_loggers)
    {
        delete logger;
    }
}
////////////////////////////////////////////////////////////////////////////////
Logger& LogManager::log()
{
    return *m_loggers[0];
}
////////////////////////////////////////////////////////////////////////////////
void setGlobalLogger(LogManager& log)
{
    gLog = &log;
}
////////////////////////////////////////////////////////////////////////////////
LogManager& log()
{
    return *gLog;
}
////////////////////////////////////////////////////////////////////////////////
