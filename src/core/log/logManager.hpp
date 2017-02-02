#ifndef __LOGMANAGER_HPP__
#define __LOGMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "logger.hpp"
#include "loggerFile.hpp"
#include "loggerGroup.hpp"
#include "loggerNull.hpp"
#include "loggerStream.hpp"
#include "core/engine_export.h"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT LogManager
{
public:
    LogManager();
    ~LogManager();

    Logger& log();

private:
    std::vector<Logger*> m_loggers;
};
////////////////////////////////////////////////////////////////////////////////
/// Global logger access
void setGlobalLogger(LogManager& log);
LogManager ENGINE_EXPORT & log();
////////////////////////////////////////////////////////////////////////////////
#endif // __LOGMANAGER_HPP__
