// #ifndef __TESTLUA_HPP__
// #define __TESTLUA_HPP__
// ////////////////////////////////////////////////////////////////////////////////
// #include <lua.hpp>
// #include <iostream>
// #include <sstream>
// ////////////////////////////////////////////////////////////////////////////////
// class Foo
// {
// public:
// 	Foo(const std::string & name) : name(name)
// 	{
// 		std::cout << "Foo is born" << std::endl;
// 	}

// 	std::string Add(int a, int b)
// 	{
// 		std::stringstream ss;
// 		ss << name << ": " << a << " + " << b << " = " << (a+b);
// 		return ss.str();
// 	}

// 	~Foo()
// 	{
// 		std::cout << "Foo is gone" << std::endl;
// 	}

// private:
// 	std::string name;
// };

// int luaTest();
// ////////////////////////////////////////////////////////////////////////////////
// #endif // __TESTLUA_HPP__
