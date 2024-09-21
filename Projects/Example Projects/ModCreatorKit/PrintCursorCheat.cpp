#include "stdafx.h"
#include "PrintCursorCheat.h"

void PrintCursorCheat::ParseLine(const ArgScript::Line& line)
{
	App::ConsolePrintF("Current Cursor ID: 0x%x", CursorManager.GetActiveCursor());
}

const char* PrintCursorCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Prints the ID of the current cursor to the console.";
	}
	else {
		return "DevPrintCursor: Prints the ID of the current cursor to the console.";
	}
}