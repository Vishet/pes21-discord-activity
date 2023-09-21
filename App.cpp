#include "App.h"

#include <csignal>
#include <thread>
#include <iostream>
#include <sstream>

App::App() :
	pes(),
    discord()
{
    std::signal(SIGINT, [](int) { interrupted = true; });
}

int App::Run()
{
    pes.CatchProcess();
    discord.Init();

    while (!interrupted)
    {
        if (pes.IsClosing()) break;
        Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}

void App::Update()
{
    system("cls");

    if (!pes.IsInGame())
    {
        std::cout << "In menu";
        discord.SetDetails("In menu");
        discord.SetState("");
        discord.UpdateActivity();
        discord.Update();
        return;
    }

    std::string homeTeamName = pes.GetHomeTeamName();
    std::string awayTeamName = pes.GetAwayTeamName();
    unsigned int homeScore = pes.GetHomeTeamScore();
    unsigned int awayScore = pes.GetAwayTeamScore();
    unsigned int seconds = pes.GetSeconds();
    unsigned int minutes = pes.GetMinutes();

    std::ostringstream info;
    info << "Home team name: " << homeTeamName << std::endl
        << "Away team name: " << awayTeamName << std::endl
        << "Time: " << minutes << ':' << seconds << std::endl
        << homeTeamName << ' ' << homeScore << " x " << awayScore << ' ' << awayTeamName;

    std::cout << info.str();

    std::ostringstream timeInfo;
    timeInfo << "In game " << minutes << '\'';
    discord.SetDetails(timeInfo.str().c_str());

    std::ostringstream scoreBoard;
    scoreBoard << homeTeamName << ' ' << homeScore << " x " << awayScore << ' ' << awayTeamName;
    discord.SetState(scoreBoard.str().c_str());

    discord.UpdateActivity();
    discord.Update();
}
