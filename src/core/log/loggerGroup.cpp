////////////////////////////////////////////////////////////////////////////////
#include "loggerGroup.hpp"
////////////////////////////////////////////////////////////////////////////////
LoggerGroup::LoggerGroup(const std::string& name)
    : Logger(name)
{
}
////////////////////////////////////////////////////////////////////////////////
LoggerGroup::~LoggerGroup()
{
}
////////////////////////////////////////////////////////////////////////////////
void LoggerGroup::addLogger(Logger* logger)
{
    m_loggers.push_back(logger);
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(const LogLine& line)
{
    for (Logger* logger : m_loggers)
    {
        *logger << line.getBuf();
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(long rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(unsigned long rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(bool rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(short rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(unsigned short rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(int rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(unsigned int rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(long long rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(unsigned long long rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(double rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(float rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(long double rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(const void* rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(const char* rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(const std::string& rhs)
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(std::ostream& (*rhs)(std::ostream&))
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(std::ios& (*rhs)(std::ios&))
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerGroup::operator<<(std::ios_base& (*rhs)(std::ios_base&))
{
    for (Logger* logger : m_loggers)
    {
        *logger << rhs;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
