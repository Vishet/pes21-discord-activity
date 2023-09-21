#include "App.h"
#include <exception>
#include "discord-files/discord.h"

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