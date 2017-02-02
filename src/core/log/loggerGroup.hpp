#ifndef __LOGGERGROUP_HPP__
#define __LOGGERGROUP_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "logger.hpp"
#include <vector>
////////////////////////////////////////////////////////////////////////////////
/// \brief Logger holding other loggers
////////////////////////////////////////////////////////////////////////////////
class LoggerGroup : public Logger
{
public:
    LoggerGroup(const std::string& name);
    virtual ~LoggerGroup() override;

    void addLogger(Logger* logger);

    virtual Logger& operator<<(const LogLine& line) override;

    virtual Logger& operator<<(long rhs) override;
    virtual Logger& operator<<(unsigned long rhs) override;
    virtual Logger& operator<<(bool rhs) override;
    virtual Logger& operator<<(short rhs) override;
    virtual Logger& operator<<(unsigned short rhs) override;
    virtual Logger& operator<<(int rhs) override;
    virtual Logger& operator<<(unsigned int rhs) override;
    virtual Logger& operator<<(long long rhs) override;
    virtual Logger& operator<<(unsigned long long rhs) override;
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
    std::vector <Logger*> m_loggers;    ///< Array of loggers
};
////////////////////////////////////////////////////////////////////////////////
#endif // __LOGGERGROUP_HPP__
