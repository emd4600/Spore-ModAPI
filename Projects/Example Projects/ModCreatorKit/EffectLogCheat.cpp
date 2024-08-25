#include "stdafx.h"
#include "EffectLogCheat.h"
#include <Spore/Swarm/cEffectsManager.h>

bool EffectLogCheat::IsEnabled = false;

member_detour(ReadEffect_detour, Swarm::cEffectsManager, int(uint32_t, uint32_t)) {
	int detoured(uint32_t instanceId, uint32_t groupId) {
		if (EffectLogCheat::IsEnabled && instanceId != 0)
		{
			App::ConsolePrintF("devEffectLog: loaded effect ID:    0x%x", instanceId);
		}
		return original_function(this, instanceId, groupId); //And call the original function with the new instance ID.
	}
};

void EffectLogCheat::AttachDetour() {
	ReadEffect_detour::attach(GetAddress(Swarm::cEffectsManager, GetDirectoryAndEffectIndex));
}

void EffectLogCheat::ParseLine(const ArgScript::Line& line)
{
	auto args = line.GetArguments(1);
	EffectLogCheat::IsEnabled = mpFormatParser->ParseBool(args[0]);
}

const char* EffectLogCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "Usage: animLog on/off. If enabled, every time an animation is loaded it will print its ID.";
}