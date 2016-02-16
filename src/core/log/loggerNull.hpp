#ifndef __LOGGERNULL_HPP__
#define __LOGGERNULL_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "logger.hpp"
#include <string>
#include <streambuf>
////////////////////////////////////////////////////////////////////////////////
/// \brief Null logger, no action
////////////////////////////////////////////////////////////////////////////////
class LoggerNull : public Logger
{
public:
    LoggerNull(const std::string& name);
    virtual ~LoggerNull() override;

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
};
////////////////////////////////////////////////////////////////////////////////
#endif // __LOGGERNULL_HPP__
