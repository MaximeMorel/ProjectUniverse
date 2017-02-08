////////////////////////////////////////////////////////////////////////////////
#include "engine.hpp"
#include "application.hpp"
#include "core/tools/filetools.hpp"
#include <iostream>
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#include <Windows.h>
#include <tchar.h>
#endif
////////////////////////////////////////////////////////////////////////////////
int enginemain(int argc, char **argv)
{
    FileTools::chdirGame();

    std::cout << "Start...\n";
    Engine engine("main");

    // get command line parameters first as they have highest priority
    engine.parseArgs(argc, argv);

    PluginAppPtr app = engine.plugins().loadApp();
    if (app && app->isValid() && engine.init(argc, argv))
    {
        engine.log().log() << app << "\n";
        Application* a = app->getLibInstance(&engine);
        if (a)
            a->run();
    }
    engine.log().log() << "main exit..." << std::endl;
    engine.plugins().flushPlugins();
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
int CALLBACK WinMain(
                     _In_ HINSTANCE hInstance,
                     _In_ HINSTANCE hPrevInstance,
                     _In_ LPSTR     lpCmdLine,
                     _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = _T("win32app");
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(nullptr,
                   _T("Call to RegisterClassEx failed!"),
                   _T("Win32 Guided Tour"),
                   MB_OK);

        return 1;
    }

    return enginemain(__argc, __argv);
}
#elif defined(__linux__) || defined(__linux) || defined(linux)
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
    return enginemain(argc, argv);
}
#endif
////////////////////////////////////////////////////////////////////////////////
