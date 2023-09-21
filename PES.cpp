#include "PES.h"
#include <TlHelp32.h>
#include <Psapi.h>

PES::~PES()
{
    CloseHandle(process);
}

void PES::CatchProcess()
{
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 pe32{};
    pe32.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hProcessSnap, &pe32);

    do
    {
        if (strcmp(pe32.szExeFile, "FL_2023.exe") == 0)
        {
            process = OpenProcess(PROCESS_ALL_ACCESS, NULL, pe32.th32ProcessID);

            HANDLE hPesSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);
            MODULEENTRY32 me32{};
            me32.dwSize = sizeof(MODULEENTRY32);
            Module32First(hPesSnap, &me32);
            do
            {
                if (strcmp(me32.szModule, "FL_2023.exe") == 0)
                    break;
            } while (Module32Next(hPesSnap, &me32));
            CloseHandle(hPesSnap);
            if (strcmp(me32.szModule, "FL_2023.exe") != 0)
                throw "Couldn't find FL_2023.exe module";

            baseAddress = reinterpret_cast<DWORD64>(me32.hModule);

            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    if (!process)
        throw "Couldn't find pes address";

    CloseHandle(hProcessSnap);
}

std::string PES::GetHomeTeamName() const
{
    DWORD64 staticAddress = baseAddress + teamNameStatic;

    DWORD64 address2{};
    if (!ReadProcessMemory(process, (void*)staticAddress, &address2, 8, NULL)) throw;
    address2 += teamOffset;

    DWORD64 address{};
    if (!ReadProcessMemory(process, (void*)address2, &address, 8, NULL)) throw;
    address += homeOffset;

    char buffer[64]{};
    if (!ReadProcessMemory(process, (void*)address, &buffer, 64, NULL)) throw;

    return buffer;
}

std::string PES::GetAwayTeamName() const
{
    DWORD64 staticAddress = baseAddress + teamNameStatic;

    DWORD64 address2{};
    if (!ReadProcessMemory(process, (void*)staticAddress, &address2, 8, NULL)) throw;
    address2 += teamOffset;

    DWORD64 address{};
    if (!ReadProcessMemory(process, (void*)address2, &address, 8, NULL)) throw;
    address += awayOffset;

    char buffer[64]{};
    if (!ReadProcessMemory(process, (void*)address, &buffer, 64, NULL)) throw;

    return buffer;
}

unsigned int PES::GetSeconds() const
{
    DWORD64 staticAddress = baseAddress + timeSecondsStatic;

    DWORD64 address{};
    if(!ReadProcessMemory(process, (void*)staticAddress, &address, 8, NULL)) throw;
    address += timeSecondsOffset;

    int seconds = 0;
    if(!ReadProcessMemory(process, (void*)address, &seconds, 4, NULL)) throw;

    return seconds;
}

unsigned int PES::GetMinutes() const
{
    DWORD64 staticAddress = baseAddress + timeMinutesStatic;

    DWORD64 address3{};
    if (!ReadProcessMemory(process, (void*)staticAddress, &address3, 8, NULL)) throw;
    address3 += timeMinutesOffset;

    DWORD64 address2{};
    if (!ReadProcessMemory(process, (void*)address3, &address2, 8, NULL)) throw;
    address2 += timeMinutesOffset2;

    DWORD64 address{};
    if (!ReadProcessMemory(process, (void*)address2, &address, 8, NULL)) throw;
    address += timeMinutesOffset3;

    int minutes{};
    if (!ReadProcessMemory(process, (void*)address, &minutes, 4, NULL)) throw;

    return minutes;
}

unsigned int PES::GetHomeTeamScore() const
{
    DWORD64 staticAddress = baseAddress + scoreStatic;

    DWORD64 address3{};
    if (!ReadProcessMemory(process, (void*)staticAddress, &address3, 8, NULL)) throw;
    address3 += scoreOffset;

    DWORD64 address2{};
    if (!ReadProcessMemory(process, (void*)address3, &address2, 8, NULL)) throw;
    address2 += scoreOffset2;

    DWORD64 address{};
    if (!ReadProcessMemory(process, (void*)address2, &address, 8, NULL)) throw;
    address += scoreHomeOffset;

    unsigned int score{};
    if (!ReadProcessMemory(process, (void*)address, &score, 4, NULL)) throw;

    return score;
}

unsigned int PES::GetAwayTeamScore() const
{
    DWORD64 staticAddress = baseAddress + scoreStatic;

    DWORD64 address3{};
    if (!ReadProcessMemory(process, (void*)staticAddress, &address3, 8, NULL)) throw;
    address3 += scoreOffset;

    DWORD64 address2{};
    if (!ReadProcessMemory(process, (void*)address3, &address2, 8, NULL)) throw;
    address2 += scoreOffset2;

    DWORD64 address{};
    if (!ReadProcessMemory(process, (void*)address2, &address, 8, NULL)) throw;
    address += scoreAwayOffset;

    unsigned int score{};
    if (!ReadProcessMemory(process, (void*)address, &score, 4, NULL)) throw;

    return score;
}


