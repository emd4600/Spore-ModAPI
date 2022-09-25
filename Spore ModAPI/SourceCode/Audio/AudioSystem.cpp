#ifndef MODAPI_DLL_EXPORT
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

#include <Spore\Audio\AudioSystem.h>

namespace Audio
{
	auto_STATIC_METHOD_(AudioSystem, AudioSystem*, Get);
}

auto_STATIC_METHOD_VOID(Audio, PlayAudio, Args(uint32_t soundID, Audio::AudioTrack track), Args(soundID, track));
auto_STATIC_METHOD_VOID(Audio, StopAudio, Args(Audio::AudioTrack track, int arg2), Args(track, arg2));

auto_STATIC_METHOD_VOID(Audio, PlayProceduralAudio,
	Args(uint32_t audioID, AudioTrack track, const Math::Vector3& position), 
	Args(audioID, track, position));

auto_STATIC_METHOD_VOID(Audio, SetPropertyString,
	Args(AudioTrack track, uint32_t propertyID, const char* pValue),
	Args(track, propertyID, pValue));

auto_STATIC_METHOD_VOID(Audio, SetProperty,
	Args(AudioTrack track, uint32_t propertyID, float floatValue, int intValue),
	Args(track, propertyID, floatValue, intValue));

#endif
