#include "stdafx.h"
#include "SFXLogCheat.h"


bool SFXLogCheat::IsEnabled = false;

// Detour the audio playing func
static_detour(PlayAudio_detour, void(uint32_t, Audio::AudioTrack)) {
	void detoured(uint32_t soundID, Audio::AudioTrack track) {
		original_function(soundID, track);
		if (SFXLogCheat::IsEnabled && soundID != 0)
		{
			App::ConsolePrintF("devSFXLog: playing Audio ID:    0x%x", soundID);
		}
	}
};

void SFXLogCheat::AttachDetour() {
	PlayAudio_detour::attach(GetAddress(Audio, PlayAudio));
}

void SFXLogCheat::ParseLine(const ArgScript::Line& line)
{
	auto args = line.GetArguments(1);
	SFXLogCheat::IsEnabled = mpFormatParser->ParseBool(args[0]);
}

const char* SFXLogCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "Usage: sfxLog on/off. If enabled, every time a UI sound effect is played it will print its ID. Does not include creature voices or world sounds.";
}
