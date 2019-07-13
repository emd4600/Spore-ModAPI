/****************************************************************************
* Copyright (C) 2019 Eric Mor
*
* This file is part of Spore ModAPI.
*
* Spore ModAPI is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/
#pragma once

#include <Spore\Internal.h>

namespace Audio
{
	class AudioSystem
	{
		//PLACEHODER we might need to complete this

		/* 00h */	int func00h();
		/* 04h */	int func04h();
		/* 08h */	int func08h();
		/* 0Ch */	int func0Ch();
		/* 10h */	int func10h();
		/* 14h */	int func14h();
		/* 18h */	int func18h();
		/* 1Ch */	int func1Ch();

	public:
		/* 20h */	virtual AudioSystem* func20h();

		static void PlayAudio(uint32_t soundID, AudioSystem* system);

		static AudioSystem* Get();
	};

	inline void PlayAudio(uint32_t soundID) {
		AudioSystem::PlayAudio(soundID, AudioSystem::Get()->func20h());
	}

	namespace Addresses(AudioSystem)
	{
		DeclareAddress(Get, SelectAddress(0xA20620, NO_ADDRESS, 0xA20670));
		DeclareAddress(PlayAudio, SelectAddress(0x436040, NO_ADDRESS, 0x436390));
	}
}