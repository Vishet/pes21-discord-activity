#pragma once

#include "PES.h"
#include "Discord.h"

class App
{
public:
	App();

	int Run();

private:
	PES pes;
	Discord discord;
	inline static bool interrupted{ false };

private:
	void Update();
};