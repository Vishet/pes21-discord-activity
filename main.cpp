#include "PES.h"
#include <windows.h>
#include <exception>

int APIENTRY WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    try
    {
        PES pes;
        pes.CatchProcess();
        DWORD64 baseAddress = pes.GetBaseAddress();
        std::string homeName = pes.GetHomeTeamName();
        std::string awayName = pes.GetAwayTeamName();
        unsigned int seconds = pes.GetSeconds();
        unsigned int minutes = pes.GetMinutes();
        unsigned int homeScore = pes.GetHomeTeamScore();
        unsigned int awayScore = pes.GetAwayTeamScore();
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

    return 0;
}