#pragma once

#include <Spore\BasicIncludes.h>

class UIInspectCheat 
	: public ArgScript::ICommand
	, public UTFWin::IWinProc
{
public:
	UIInspectCheat();
	~UIInspectCheat();

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;

	int GetPriority() const override;
	int GetEventFlags() const override;
	bool HandleUIMessage(UTFWin::IWindow* pWindow, const UTFWin::Message& message) override;

private:
	bool wasIgnoringMouse;
	bool useBreakpoint;
};

