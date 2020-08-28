#include "stdafx.h"
#include "UILogCheat.h"

bool UILogCheat::IsEnabled = false;

member_detour(ReadSPUI_detour, UTFWin::UILayout,  bool(const ResourceKey&, bool, uint32_t)) {
	bool detoured(const ResourceKey& name, bool arg_4, uint32_t arg_8) {
		if (UILogCheat::IsEnabled)
		{
			App::ConsolePrintF("devLogUI: loaded 0x%x.spui", name);
		}
		return original_function(this, name, arg_4, arg_8);
	}
};

member_detour(ReadSPUIName_detour, UTFWin::UILayout, bool(const char16_t*, uint32_t, bool, uint32_t)) {
	bool detoured(const char16_t* name, uint32_t arg_4, bool arg_8, uint32_t arg_C) {
		if (UILogCheat::IsEnabled)
		{
			App::ConsolePrintF("devLogUI: loaded %ls.spui", name);
		}
		return original_function(this, name, arg_4, arg_8, arg_C);
	}
};


void UILogCheat::AttachDetour() {
	ReadSPUI_detour::attach(GetAddress(UTFWin::UILayout, Load));
	ReadSPUIName_detour::attach(GetAddress(UTFWin::UILayout, LoadByName));
}

void UILogCheat::ParseLine(const ArgScript::Line& line)
{
	auto args = line.GetArguments(1);
	UILogCheat::IsEnabled = mpFormatParser->ParseBool(args[0]);
}

const char* UILogCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "Usage: devLogUI on/off. If enabled, every time an SPUI (Spore User Interface) is loaded it will print its ID.";
}