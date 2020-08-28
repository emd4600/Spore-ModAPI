#include "stdafx.h"
#include "AnimLogCheat.h"
#include <Spore\Anim\SPAnimation.h>

bool AnimLogCheat::IsEnabled = false;

static_detour(ReadAnimation_detour, Anim::SPAnimation*(int, const char*, uint32_t)) {
	Anim::SPAnimation* detoured(int arg0, const char* name, uint32_t instanceID) {
		Anim::SPAnimation* anim = original_function(arg0, name, instanceID);
		if (anim) {
			if (AnimLogCheat::IsEnabled)
			{
				if (name && !string(name).empty()) App::ConsolePrintF("devLogAnim: loaded %s.animation    (address 0x%x)", name, anim);
				else if (strlen(anim->path) > 0) App::ConsolePrintF("devLogAnim: loaded %s    (address 0x%x)", anim->path, anim);
				else App::ConsolePrintF("devLogAnim: loaded 0x%x.animation    (address 0x%x)", instanceID, anim);
			}
		}
		return anim;
	}
};

void AnimLogCheat::AttachDetour() {
	ReadAnimation_detour::attach(Address(ModAPI::ChooseAddress(0x99EC00, 0x99ECA0)));
}

void AnimLogCheat::ParseLine(const ArgScript::Line& line)
{
	auto args = line.GetArguments(1);
	AnimLogCheat::IsEnabled = mpFormatParser->ParseBool(args[0]);
}

const char* AnimLogCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "Usage: animLog on/off. If enabled, every time an animation is loaded it will print its ID.";
}