#ifndef __LOGGERSTREAM_HPP__
#define __LOGGERSTREAM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "logger.hpp"
#include <sstream>
////////////////////////////////////////////////////////////////////////////////
class LoggerStream : public Logger
{
public:
    LoggerStream(const std::string& name, std::ostream& stream);
    virtual ~LoggerStream();

    virtual Logger& operator<<(const LogLine& line) override;

    virtual Logger& operator<<(long rhs) override;
    virtual Logger& operator<<(unsigned long rhs) override;
    virtual Logger& operator<<(bool rhs) override;
    virtual Logger& operator<<(short rhs) override;
    virtual Logger& operator<<(unsigned short rhs) override;
    virtual Logger& operator<<(int rhs) override;
    virtual Logger& operator<<(unsigned int rhs) override;
    virtual Logger& operator<<(double rhs) override;
    virtual Logger& operator<<(float rhs) override;
    virtual Logger& operator<<(long double rhs) override;
    virtual Logger& operator<<(const void* rhs) override;
    virtual Logger& operator<<(const char* rhs) override;

    virtual Logger& operator<<(const std::string& rhs) override;

    virtual Logger& operator<<(std::ostream& (*rhs)(std::ostream&)) override;
    virtual Logger& operator<<(std::ios& (*rhs)(std::ios&)) override;
    virtual Logger& operator<<(std::ios_base& (*rhs)(std::ios_base&)) override;

private:
    std::ostream m_outStream;   ///< Out stream
};
////////////////////////////////////////////////////////////////////////////////
#endif // __LOGGERSTREAM_HPP__
