#pragma once

#include <Windows.h>
#include <string>

class PES
{
public:
	PES() = default;
	~PES();

	PES(const PES&) = delete;
	PES(const PES&&) = delete;
	PES operator=(const PES&) = delete;
	PES operator=(const PES&&) = delete;

	void CatchProcess();
	inline DWORD64 GetBaseAddress() const noexcept { return baseAddress; }

	std::string GetHomeTeamName() const;
	std::string GetAwayTeamName() const;
	unsigned int GetSeconds() const;
	unsigned int GetMinutes() const;

	unsigned int GetHomeTeamScore() const;
	unsigned int GetAwayTeamScore() const;

private:
	HANDLE process{};
	DWORD64 baseAddress{};

	static constexpr auto teamNameStatic    = 0x3705E10;
	static constexpr auto teamOffset		= 0x50;
	static constexpr auto homeOffset		= 0x35A9C;
	static constexpr auto awayOffset		= 0x3612C;

	static constexpr auto timeSecondsStatic = 0x37C3CE0;
	static constexpr auto timeSecondsOffset = 0x58;

	static constexpr auto timeMinutesStatic = 0x36F0260;
	static constexpr auto timeMinutesOffset = 0x18EC0;
	static constexpr auto timeMinutesOffset2 = 0x1118;
	static constexpr auto timeMinutesOffset3 = 0x12C;

	static constexpr auto scoreStatic		= 0x36F9B38;
	static constexpr auto scoreOffset		= 0x58;
	static constexpr auto scoreOffset2		= 0x1118;

	static constexpr auto scoreHomeOffset	= 0x120;
	static constexpr auto scoreAwayOffset	= 0x124;
};

