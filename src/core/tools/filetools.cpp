////////////////////////////////////////////////////////////////////////////////
#include "filetools.hpp"
#include <string>
#include <algorithm>
////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <Windows.h>
#include <ShlObj.h>
#include <direct.h>
#elif defined(__linux__) || defined(__linux) || defined(linux)
#include <unistd.h>
#include <sys/stat.h>
#include <climits>
#include <cstring>
#include <cstdlib>
#endif
////////////////////////////////////////////////////////////////////////////////
char* FileTools::getcwd(char* buf, size_t size)
{
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
    return _getcwd(buf, static_cast<int>(size));
#elif defined(__linux__) || defined(__linux) || defined(linux)
    return ::getcwd(buf, size);
#endif
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////
bool FileTools::mkdir(const std::string& path)
{
	bool res = true;

	size_t pos = 0;
	do
	{
		pos = path.find('/', pos + 1);
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
		res = (CreateDirectory(path.substr(0, pos).c_str(), nullptr) == 0 ? false : true);
#elif defined(__linux__) || defined(__linux) || defined(linux)
		res = ::mkdir(path.substr(0, pos).c_str(), S_IRWXU | S_IRGRP | S_IROTH | S_IXGRP | S_IXOTH);
#endif
	} while (pos != std::string::npos);
    return res;
}
////////////////////////////////////////////////////////////////////////////////
bool FileTools::mkdirGame(const char* app)
{
	std::string path;
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
	PWSTR home = nullptr;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &home);
	if (home == nullptr)
		return false;
	std::wstring wstrhome(home);
	path = std::string(wstrhome.begin(), wstrhome.end());
	std::replace(path.begin(), path.end(), '\\', '/');
	CoTaskMemFree(home);
#elif defined(__linux__) || defined(__linux) || defined(linux)
    char* home = getenv("HOME");
	if (home == nullptr)
		return false;
	path = home;
	path.append("/.config");
#endif
    path.append("/ProjectUniverse/");
    if (strlen(app) > 0)
    {
        path.append("app/");
        path.append(app);
    }
	FileTools::mkdir(path.c_str());

    return true;
}
////////////////////////////////////////////////////////////////////////////////
bool FileTools::chdirGame()
{
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
	WCHAR filename[MAX_PATH];
	DWORD len = GetModuleFileNameW(nullptr, filename, RTL_NUMBER_OF_V1(filename));
	if (len > 0 && len < RTL_NUMBER_OF_V1(filename))
	{
		WCHAR path[MAX_PATH];
		DWORD lenNorm = GetFullPathNameW(filename, RTL_NUMBER_OF_V1(path), path, nullptr); // normalize
		if (lenNorm > 0 && lenNorm < RTL_NUMBER_OF_V1(path))
		{
			DWORD i = lenNorm - 1;
			int count = 0;
			while (count < 2 && i >= 0)
			{
				if (path[i] == L'\\')
					++count;
				--i;
			}
			if (count == 2)
			{
				path[i + 1] = L'\0';
				if (SetCurrentDirectoryW(path) != 0)
				{
					/*std::wstring libPath(path);
					libPath.append(L"\\lib");
					AddDllDirectory(libPath.c_str());
					libPath.append(L"\\thirdparty");
					AddDllDirectory(libPath.c_str());*/
					return true;
				}
			}
		}
	}
#elif defined(__linux__) || defined(__linux) || defined(linux)
    char buf[PATH_MAX];
    readlink("/proc/self/exe", buf, sizeof(buf));
    int count = 0;
    int i = strlen(buf) - 1;
    while (count < 2 && i >= 0)
    {
        if (buf[i] == '/')
            ++count;
        --i;
    }
    if (count == 2)
    {
        buf[i + 1] = '\0';
        return (chdir(buf) == 0);
    }
#endif
    return false;
}
////////////////////////////////////////////////////////////////////////////////
std::string FileTools::getdirGame(const char* app)
{
	std::string res;
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
	PWSTR home = nullptr;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &home);
	if (home != nullptr)
	{
		std::wstring wstrhome(home);
		res = std::string(wstrhome.begin(), wstrhome.end());
		std::replace(res.begin(), res.end(), '\\', '/');
		CoTaskMemFree(home);
	}
#elif defined(__linux__) || defined(__linux) || defined(linux)
    char* home = getenv("HOME");
	if (home)
	{
		res = home;
		res.append("/.config");
	}
#endif
	res.append("/ProjectUniverse/");
	if (strlen(app) > 0)
	{
		res.append("app/");
		res.append(app);
		res.push_back('/');
	}
	return res;
}
////////////////////////////////////////////////////////////////////////////////
