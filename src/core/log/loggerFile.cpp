////////////////////////////////////////////////////////////////////////////////
#include "loggerFile.hpp"
////////////////////////////////////////////////////////////////////////////////
LoggerFile::LoggerFile(const std::string& name, const std::string& fileName)
    : Logger(name)
    , m_outFile(fileName)
{
}
////////////////////////////////////////////////////////////////////////////////
LoggerFile::~LoggerFile()
{
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(const LogLine& line)
{
    m_outFile << line.getBuf();
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(long rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(unsigned long rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(bool rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(short rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(unsigned short rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(int rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(unsigned int rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(long long rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(unsigned long long rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(double rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(float rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(long double rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(const void* rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(const char* rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(const std::string& rhs)
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(std::ostream& (*rhs)(std::ostream&))
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(std::ios& (*rhs)(std::ios&))
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
Logger& LoggerFile::operator<<(std::ios_base& (*rhs)(std::ios_base&))
{
    m_outFile << rhs;
    return *this;
}
////////////////////////////////////////////////////////////////////////////////
