#ifndef __LOGMANAGER_HPP__
#define __LOGMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////
ILogger& log();


class ILogger
{
public:
    ILogger& operator<< (bool val);
    ILogger& operator<< (short val);
    ILogger& operator<< (unsigned short val);
    ILogger& operator<< (int val);
    ILogger& operator<< (unsigned int val);
    ILogger& operator<< (long val);
    ILogger& operator<< (unsigned long val);
    ILogger& operator<< (long long val);
    ILogger& operator<< (unsigned long long val);
    ILogger& operator<< (float val);
    ILogger& operator<< (double val);
    ILogger& operator<< (long double val);
    ILogger& operator<< (void* val);
private:
};

class LoggerStd : public ILogger
{
public:
private:
};

class LogManager
{
public:
    LogManager();
    LogManager();

private:
    std::vector<ILogger*> m_loggers;
};

ILogger* gLog;
