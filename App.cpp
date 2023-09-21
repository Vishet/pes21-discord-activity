#include "App.h"

#include <csignal>
#include <thread>
#include <iostream>
#include <sstream>

App::App() :
	pes()
{
    std::signal(SIGINT, [](int) { interrupted = true; });
}

int App::Run()
{
    //pes.CatchProcess();

    while (!interrupted)
    {
        Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}

void App::Update()
{
    system("cls");

    /*

    unsigned int seconds = pes.GetSeconds();
    if (seconds == 0)
    {
        std::cout << "In menu";
        return;
    }

    std::string homeTeamName = pes.GetHomeTeamName();
    std::string awayTeamName = pes.GetAwayTeamName();
    unsigned int homeScore = pes.GetHomeTeamScore();
    unsigned int awayScore = pes.GetAwayTeamScore();
    unsigned int minutes = pes.GetMinutes();

    std::ostringstream oss;
    oss << "Home team name: " << homeTeamName << std::endl
        << "Away team name: " << awayTeamName << std::endl
        << "Time: " << minutes << ':' << seconds << std::endl
        << homeTeamName << ' ' << homeScore << " x " << awayScore << ' ' << awayTeamName;

    std::cout << oss.str();

    */
}
