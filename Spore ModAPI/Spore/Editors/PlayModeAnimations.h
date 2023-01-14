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

#include <Spore\Editors\PlayAnimPanel.h>

#include <EASTL\vector.h>

namespace Editors
{
	class cEditor;

	// uses amimation ID in 62E587

	class PlayModeAnimations
	{
	public:

		virtual ~PlayModeAnimations();

		virtual bool Initialize(int, int);
		virtual void Dispose();
		virtual float PlayAnimation(int, uint32_t playAnimName, bool loop, int mode, int* dstAnimIndex = nullptr);

	public:
		/// Reads all the animation panels in the 0x4060E000 folder.
		void ReadAnimations();

		/// Reads the .prop configuration file of a panel that contains multiple animation buttons.
		/// The files of the panel anim buttons are in the 0x4060E100 folder.
		/// @param name The ResourceKey of the .prop file.
		void ReadPanel(const ResourceKey& name);

		/// Reads the .prop configuration file of an animation button, and adds it to the given panel.
		/// @param pPanel The animation buttons panel this button must go.
		/// @param name The ResourceKey of the .prop file.
		void ReadAnimButton(PlayAnimPanel* pPanel, const ResourceKey& name);

		/// Creates all the buttons and windows that represent the animations in this object.
		void GenerateUI();

	public:
		/* 04h */	cEditor* mpEditor;  // not initialized
		/* 08h */	int field_08;  // not initialized
		/// All the PlayAnimPanel objects, ordered by the 'mnAnimPanelOrder' field.
		/* 0Ch */	eastl::vector<eastl::intrusive_ptr<PlayAnimPanel>> mPanels;

		/* 20h */	int field_20;
		/* 24h */	int field_24;  // not initialized
		/* 28h */	int field_28;  // not initialized
		/* 2Ch */	int field_2C;
		/* 30h */	int field_30;
		/* 34h */	int field_34;
		/* 38h */	int field_38;
		/* 3Ch */	int field_3C;
		/* 40h */	int field_40;
		/* 44h */	int field_44;
		/* 48h */	int field_48;
		/* 4Ch */	int field_4C;
		/* 50h */	int field_50;
		/* 54h */	int field_54;
		/* 58h */	int field_58;
		/* 5Ch */	int field_5C;
		/* 60h */	int field_60;
		/* 64h */	int field_64;
		/* 68h */	int field_68;
		/* 6Ch */	int field_6C;
		/* 70h */	int field_70;
		/* 74h */	int field_74;
		/* 78h */	int field_78;
		/* 7Ch */	int field_7C;
		/* 80h */	int field_80;
		/* 84h */	int field_84;
		/* 88h */	int field_88;
		/* 8Ch */	int field_8C;  // not initialized
	};
	ASSERT_SIZE(PlayModeAnimations, 0x90);

	namespace Addresses(PlayModeAnimations)
	{
		DeclareAddress(ReadAnimations);
		DeclareAddress(ReadPanel);
		DeclareAddress(ReadAnimButton);
		DeclareAddress(GenerateUI);
	}
}