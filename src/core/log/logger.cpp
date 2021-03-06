////////////////////////////////////////////////////////////////////////////////
#include "logger.hpp"
////////////////////////////////////////////////////////////////////////////////
Logger::Logger(const std::string& name)
    : m_name(name)
{
}
////////////////////////////////////////////////////////////////////////////////
Logger::~Logger()
{
}
////////////////////////////////////////////////////////////////////////////////
const std::string& Logger::getName() const
{
    return m_name;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
LogLine::LogLine()
    : m_buf()
{
}
////////////////////////////////////////////////////////////////////////////////
LogLine::~LogLine()
{
}
////////////////////////////////////////////////////////////////////////////////
std::string LogLine::getBuf() const
{
    return m_buf.str();
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(long rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(unsigned long rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(bool rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(short rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(unsigned short rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(int rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(unsigned int rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(double rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(float rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(long double rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(const void* rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(const char* rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(const std::string& rhs)
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(std::ostream& (*rhs)(std::ostream&))
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(std::ios& (*rhs)(std::ios&))
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
LogLine& LogLine::operator<<(std::ios_base& (*rhs)(std::ios_base&))
{
    m_buf << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
