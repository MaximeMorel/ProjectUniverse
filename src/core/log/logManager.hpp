#ifndef __LOGMANAGER_HPP__
#define __LOGMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "logger.hpp"
#include "loggerFile.hpp"
#include "loggerGroup.hpp"
#include "loggerNull.hpp"
#include "loggerStream.hpp"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class LogManager
{
public:
    LogManager();
    ~LogManager();

    Logger& log();

private:
    std::vector<Logger*> m_loggers;
};
////////////////////////////////////////////////////////////////////////////////
//ILogger* gLog;
#endif // __LOGMANAGER_HPP__
