#include "App.h"
//#include <windows.h>
#include <exception>

/*
int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    try
    {
        return App().Run();
    }
    catch (const std::exception& e)
    {
        return MessageBox(NULL, e.what(), "Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (const char* e)
    {
        return MessageBox(NULL, e, "Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        return MessageBox(NULL, "No details avaliable", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
    }
}
*/

int main()
{
    try
    {
        return App().Run();
    }
    catch (const std::exception& e)
    {
        return MessageBox(NULL, e.what(), "Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (const char* e)
    {
        return MessageBox(NULL, e, "Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        return MessageBox(NULL, "No details avaliable", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
    }
}