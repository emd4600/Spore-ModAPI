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

#include <Spore\Object.h>
#include <Spore\ResourceKey.h>

namespace Simulator
{
	enum SimulatorMessages
	{
		/// Simulator::EnterEditorMessage; Enters the correct editor modifying the specified creation.
		kMsgEnterEditor = 0x53850BAE,

		kMsgSwitchGameMode = 0x0212D3E7
	};

	class IMessageParameters
	{
	public:
		inline virtual ~IMessageParameters() {}
		virtual int AddRef() = 0;
		virtual int Release() = 0;
	};

	class EnterModeMessage
	{
		/* 08h */	uint32_t mModeID;

		/* 10h */	uint32_t mPreviousModeID;
	};

	class EnterEditorMessage : public IMessageParameters, public IVirtual
	{
	public:
		EnterEditorMessage();
		EnterEditorMessage(uint32_t editorID, ResourceKey creationName, int field_1C = 0);
		inline virtual ~EnterEditorMessage() {};

		virtual int AddRef() override;
		virtual int Release() override;

	protected:
		int mnRefCount;

	public:
		/// The ID of the editor to enter, for exmple CivAccessoriesEditorSetup
		/* 0Ch */	uint32_t mEditorID;
		/// The name of the creation, for example creature_editorModel~!0x8E6A1FF5.crt
		/* 10h */	ResourceKey mCreationName;
		/* 1Ch */	int field_1C;
	};
}