#ifndef __LOGGERFILE_HPP__
#define __LOGGERFILE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "logger.hpp"
#include <fstream>
////////////////////////////////////////////////////////////////////////////////
/*class LoggerFileBuf : public std::filebuf
{
public:
    LoggerFileBuf(const char* filename);
    virtual ~LoggerFileBuf() override;

    virtual int_type overflow(int_type c = traits_type::eof()) override;
};
////////////////////////////////////////////////////////////////////////////////
class LoggerFile : public Logger
{
public:
    LoggerFile(const std::string& name, const std::string& fileName);
    LoggerFile(const std::string& name, std::ostream& stream);
    //LoggerFile(const std::string& name, LoggerStreamBuf& buf);
    virtual ~LoggerFile() override;

private:
    LoggerFileBuf m_buf;
};*/
////////////////////////////////////////////////////////////////////////////////
class LoggerFile : public Logger
{
public:
    LoggerFile(const std::string& name, const std::string& fileName);
    virtual ~LoggerFile() override;

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
    std::ofstream m_outFile;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __LOGGERFILE_HPP__
