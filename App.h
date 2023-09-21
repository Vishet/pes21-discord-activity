#pragma once

#include "PES.h"

class App
{
public:
	App();

	int Run();

private:
	PES pes;
	inline static bool interrupted{ false };

private:
	void Update();
};