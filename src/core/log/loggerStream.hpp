#ifndef __LOGGERSTREAM_HPP__
#define __LOGGERSTREAM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "logger.hpp"
#include <sstream>
////////////////////////////////////////////////////////////////////////////////
/*class LoggerStringBuf : public std::stringbuf
{
public:
    LoggerStringBuf();//std::ostream& stream);
    virtual ~LoggerStringBuf() override;

    virtual int_type overflow(int_type c = traits_type::eof()) override;
};
////////////////////////////////////////////////////////////////////////////////
class LoggerString : public Logger
{
public:
    LoggerString(const std::string& name, std::ostream& stream);
    //LoggerString(const std::string& name, LoggerStreamBuf& buf);
    virtual ~LoggerString() override;

private:
    LoggerStringBuf m_buf;
};*/
////////////////////////////////////////////////////////////////////////////////
class LoggerStream : public Logger
{
public:
    LoggerStream(const std::string& name, std::ostream& stream);
    virtual ~LoggerStream();

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
