#include "App.h"
#include <exception>
#include "discord-files/discord.h"
#include <sstream>

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
    catch (discord::Result e)
    {
        std::ostringstream oss;
        oss << "Error code: " << std::hex << static_cast<int>(e);
        return MessageBox(NULL, oss.str().c_str(), "Discord Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (DWORD e)
    {
        std::ostringstream oss;
        oss << "Error code: " << std::hex << e;
        return MessageBox(NULL, oss.str().c_str(), "Windows Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        return MessageBox(NULL, "No details avaliable", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
    }
}