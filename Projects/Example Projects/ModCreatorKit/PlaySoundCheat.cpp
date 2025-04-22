#include "stdafx.h"
#include "PlaySoundCheat.h"

PlaySoundCheat::PlaySoundCheat()
{
}


PlaySoundCheat::~PlaySoundCheat()
{
}


void PlaySoundCheat::ParseLine(const ArgScript::Line& line)
{
	mParameter = line.GetArguments(1)[0];
	if (string16(mParameter).find(u"0x") == 0) {
		Audio::PlayAudio(mpFormatParser->ParseUInt(mParameter));
	}

	Audio::PlayAudio(id(mParameter));
}

const char* PlaySoundCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	return "Plays an SNR sound file by name or hash.";
}
