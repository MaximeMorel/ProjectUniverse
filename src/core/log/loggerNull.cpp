////////////////////////////////////////////////////////////////////////////////
#include "loggerNull.hpp"
////////////////////////////////////////////////////////////////////////////////
LoggerNull::LoggerNull(const std::string& name)
 : Logger(name)
{
}
////////////////////////////////////////////////////////////////////////////////
LoggerNull::~LoggerNull()
{
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(long rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(unsigned long rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(bool rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(short rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(unsigned short rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(int rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(unsigned int rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(double rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(float rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(long double rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(const void* rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(const char* rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(const std::string& rhs)
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(std::ostream& (*rhs)(std::ostream&))
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(std::ios& (*rhs)(std::ios&))
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerNull::operator<<(std::ios_base& (*rhs)(std::ios_base&))
{
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
