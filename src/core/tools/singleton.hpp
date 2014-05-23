#pragma once
#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__
////////////////////////////////////////////////////////////////////////////////
/*class SingletonManager;
class ISingleton
{
protected:
    virtual ~ISingleton()=0;

    friend class SingletonManager;
};*/
////////////////////////////////////////////////////////////////////////////////
template <class T>
class Singleton// : public ISingleton
{
public:
    static T& getInstance();
    static void destroy();

protected:
    Singleton();
    virtual ~Singleton();

private:
    /// disable copy
    Singleton(const Singleton&);
    /// disable copy
    Singleton& operator=(const Singleton&);

    static T *m_instance;   ///< instance attribute
};
////////////////////////////////////////////////////////////////////////////////
#include "singleton.inl"
////////////////////////////////////////////////////////////////////////////////
#endif // __SINGLETON_HPP__
