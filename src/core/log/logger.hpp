#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include <ostream>
#include <sstream>
////////////////////////////////////////////////////////////////////////////////
class LogLine
{
public:
    LogLine();
    ~LogLine();

    std::string getBuf() const;

    LogLine& operator<<(long rhs);
    LogLine& operator<<(unsigned long rhs);
    LogLine& operator<<(bool rhs);
    LogLine& operator<<(short rhs);
    LogLine& operator<<(unsigned short rhs);
    LogLine& operator<<(int rhs);
    LogLine& operator<<(unsigned int rhs);
    LogLine& operator<<(double rhs);
    LogLine& operator<<(float rhs);
    LogLine& operator<<(long double rhs);
    LogLine& operator<<(const void* rhs);
    LogLine& operator<<(const char* rhs);

    LogLine& operator<<(const std::string& rhs);

    LogLine& operator<<(std::ostream& (*rhs)(std::ostream&));
    LogLine& operator<<(std::ios& (*rhs)(std::ios&));
    LogLine& operator<<(std::ios_base& (*rhs)(std::ios_base&));

private:
    std::stringstream m_buf;     ///< logging buffer
};
////////////////////////////////////////////////////////////////////////////////
/// \brief Logger top class, intended to be used like an ostream
////////////////////////////////////////////////////////////////////////////////
class Logger
{
public:
    Logger(const std::string& name);
    virtual ~Logger();

    const std::string& getName() const;

    virtual Logger& operator<<(const LogLine& line)=0;

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
#define S1(x) #x
#define S2(x) S1(x)
#define FILEINFO __FILE__ ":" S2(__LINE__) " - "
////////////////////////////////////////////////////////////////////////////////
#endif // __LOGGER_HPP__
