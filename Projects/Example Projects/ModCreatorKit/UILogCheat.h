#pragma once

#include <Spore\BasicIncludes.h>

class UILogCheat
	: public ArgScript::ICommand
{
public:
	void ParseLine(const ArgScript::Line& line) override;
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

	static bool IsEnabled;

	static void AttachDetour();
};