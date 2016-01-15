#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <ostream>
#include <string>
////////////////////////////////////////////////////////////////////////////////
/*class LoggerBuf : public std::streambuf
{
public:
    LoggerBuf(std::ostream& stream);
    virtual ~LoggerBuf() override;

    virtual int_type overflow(int_type c = traits_type::eof()) override;
};
////////////////////////////////////////////////////////////////////////////////
class Logger : public std::ostream
{
public:
    Logger(const std::string& name);
    virtual ~Logger() override;

    const std::string& getName() const;

private:
    std::string m_name;     ///< Logger name
};*/
////////////////////////////////////////////////////////////////////////////////
class Logger
{
public:
    Logger(const std::string& name);
    virtual ~Logger();

    const std::string& getName() const;

    virtual Logger& operator<<(long rhs)=0;
    virtual Logger& operator<<(unsigned long rhs)=0;
    virtual Logger& operator<<(bool rhs)=0;
    virtual Logger& operator<<(short rhs)=0;
    virtual Logger& operator<<(unsigned short rhs)=0;
    virtual Logger& operator<<(int rhs)=0;
    virtual Logger& operator<<(unsigned int rhs)=0;
    virtual Logger& operator<<(double rhs)=0;
    virtual Logger& operator<<(float rhs)=0;
    virtual Logger& operator<<(long double rhs)=0;
    virtual Logger& operator<<(const void* rhs)=0;
    virtual Logger& operator<<(const char* rhs)=0;

    virtual Logger& operator<<(const std::string& rhs)=0;

    virtual Logger& operator<<(std::ostream& (*rhs)(std::ostream&))=0;
    virtual Logger& operator<<(std::ios& (*rhs)(std::ios&))=0;
    virtual Logger& operator<<(std::ios_base& (*rhs)(std::ios_base&))=0;

private:
    std::string m_name;     ///< Logger name
};
////////////////////////////////////////////////////////////////////////////////
#endif // __LOGGER_HPP__
