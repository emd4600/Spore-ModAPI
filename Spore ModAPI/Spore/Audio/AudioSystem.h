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

#include <Spore\MathUtils.h>
#include <Spore\Internal.h>

namespace Audio
{
	typedef int AudioTrack;

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
		/// Creates a new audio channel (an individual track where only one sound can be played at the same time)
		/// and returns the index used to reference it.
		/// @returns 
		/* 20h */	virtual AudioTrack CreateAudioTrack();

		static AudioSystem* Get();
	};

	namespace Addresses(AudioSystem)
	{
		DeclareAddress(Get);
		// Kept here for backwards compatibility
		DeclareAddress(PlayAudio);
	}

	/// Creates a new audio channel (an individual track where only one sound can be played at the same time)
	/// and returns the index used to reference it.
	/// @returns 
	inline AudioTrack CreateAudioTrack() {
		return AudioSystem::Get()->CreateAudioTrack();
	}

	/// Plays a standard sound (`.snr` file?) in the given audio track.
	/// @param soundID
	/// @param track The track index
	void PlayAudio(uint32_t soundID, AudioTrack track);

	/// Creates a new track and plays the given sound on it.
	/// @param soundID
	/// @returns The track index
	inline AudioTrack PlayAudio(uint32_t soundID) {
		auto track = AudioSystem::Get()->CreateAudioTrack();
		PlayAudio(soundID, track);
		return track;
	}

	/// Stops playing a given audio track and destroys it.
	/// @param track
	/// @param param2
	void StopAudio(AudioTrack track, int param2 = 0);

	/// Plays a procedural audio (`.pd` files??) at a specific position.
	/// @param audioID
	/// @param track
	/// @param position
	void PlayProceduralAudio(uint32_t audioID, AudioTrack track, const Math::Vector3& position);

	/// Sets a string property for the given track.
	/// @param track
	/// @param propertyID
	/// @param pValue
	void SetPropertyString(AudioTrack track, uint32_t propertyID, const char* pValue);

	/// Sets an int/bool/float property for the given track.
	/// @param track
	/// @param propertyID
	/// @param floatValue
	/// @param intValue
	void SetProperty(AudioTrack track, uint32_t propertyID, float floatValue, int intValue);
}

namespace Addresses(Audio)
{
	DeclareAddress(PlayAudio);
	DeclareAddress(StopAudio);  // 0x571F40, 0x572020
	DeclareAddress(PlayProceduralAudio);  // 0x571EA0, 0x571F80
	DeclareAddress(SetProperty);  // 0x4360B0, 0x436400
	DeclareAddress(SetPropertyString);  // 0x571F90, 0x572070
}