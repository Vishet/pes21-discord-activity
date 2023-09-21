#include "Discord.h"

#include <chrono>
#include <ctime>
#include <iostream>

void Discord::Init()
{
    discord::Core* pCore{};
    auto result = discord::Core::Create(
        clientId,
        DiscordCreateFlags_Default,
        &pCore
    );

    this->pCore.reset(pCore);

    discord::Activity activity{};
    activity.SetDetails("In game");
    activity.SetState("Barcelona 3 x 2 Chelsea");
    activity.GetAssets().SetLargeImage(largeImage);
    activity.GetAssets().SetLargeText(largeText);
    activity.SetType(discord::ActivityType::Playing);

    time_t now = time(0);
    activity.GetTimestamps().SetStart(now);

    pCore->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
        std::cout << ((result == discord::Result::Ok) ? "Succeeded" : "Failed")
            << " updating activity!\n";
    });
}

void Discord::Update()
{
    pCore->RunCallbacks();
}
