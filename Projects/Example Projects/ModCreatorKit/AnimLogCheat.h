#pragma once

#include <Spore\BasicIncludes.h>

static_detour(ReadAnimation_detour, void(int, const char*, uint32_t))
{
public:
	static bool IsEnabled;

	static void AttachDetour();
};

class AnimLogCheat
	: public ArgScript::ICommand
{
public:
	void ParseLine(const ArgScript::Line& line) override;
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;
};