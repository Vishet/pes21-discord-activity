#pragma once

#include "discord-files/discord.h"
#include <memory>

class Discord
{
public:
	Discord() = default;

	void Init();
	void Update();

private:
	std::unique_ptr<discord::Core> pCore{};
	static constexpr discord::ClientId clientId = 1153518052109991986;
	static constexpr const char* largeImage = "pes_2021_icon";
	static constexpr const char* largeText = "PES 2021";
};