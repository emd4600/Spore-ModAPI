#include "stdafx.h"
#include "AnimLogCheat.h"

bool ReadAnimation_detour::IsEnabled = false;

void ReadAnimation_detour::DETOUR(int arg0, const char* name, uint32_t instanceID) {
	if (ReadAnimation_detour::IsEnabled) 
	{
		if (name && !string(name).empty()) App::ConsolePrintF("Anim loaded: %s", name);
		else App::ConsolePrintF("Anim loaded: 0x%x", instanceID);
	}
	return original_function(arg0, name, instanceID);
}

void ReadAnimation_detour::AttachDetour() {
	ReadAnimation_detour::attach(Address(ModAPI::ChooseAddress(0x99EC00, 0x99ECA0)));
}

void AnimLogCheat::ParseLine(const ArgScript::Line& line)
{
	auto args = line.GetArguments(1);
	ReadAnimation_detour::IsEnabled = mpFormatParser->ParseBool(args[0]);
}

const char* AnimLogCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "Usage: animLog on/off. If enabled, every time an animation is loaded it will print its ID.";
}